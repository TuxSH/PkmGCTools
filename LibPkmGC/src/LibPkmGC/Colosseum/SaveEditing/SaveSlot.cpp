/*
* Copyright (C) TuxSH 2015
* This file is part of LibPkmGC.
*
* LibPkmGC is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* LibPkmGC is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with LibPkmGC.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <LibPkmGC/Colosseum/SaveEditing/SaveSlot.h>
#include <LibPkmGC/Core/Crypto.h>

namespace LibPkmGC {
namespace Colosseum {
namespace SaveEditing {

inline void decrypt_in_place_impl(u8* data, u8 digest[20]) {
	u8 key[20];
	std::copy(digest, digest + 20, key);

	u32 K[5], D[5];

	std::copy(key, key + 20, (u8*)K); // these copy calls will be optimized by the compiler

	for (size_t i = 0; i < 5; ++i) // unrolling the loops manually has no influence over the performance 
		K[i] = ~K[i]; // 'NOT' the 20 digest bytes

	std::copy((u8*)K, (u8*)(K + 5), key);

	for (size_t i = 0x18; i < 0x1dfd8; i += 20) {
		Crypto::sha1(data + i, data + i + 20, key); // hash the 20 bytes of encrypted data -- there are the next key

		std::copy(data + i, data + i + 20, (u8*)D);
		
		for (size_t j = 0; j < 5; ++j)
			D[j] ^= K[j]; // 'XOR' the data with the current digest

		std::copy((u8*)D, (u8*)(D + 5), data + i);
		std::copy(key, key + 20, (u8*)K);
	}

}


inline void encrypt_impl(u8* data, u8* outData, u8 digest[20]) {
	u8 key[20];
	std::copy(digest, digest + 20, key);

	u32 K[5], D[5], OD[5];

	std::copy(key, key + 20, (u8*)K); // these copy calls will be optimized by the compiler

	for (size_t i = 0; i < 5; ++i) // unrolling the loops manually has no influence over the performance 
		K[i] = ~K[i]; // 'NOT' the 20 digest bytes

	std::copy((u8*)K, (u8*)(K + 5), key);

	for (size_t i = 0x18; i < 0x1dfd8; i += 20) {
		std::copy(data + i, data + i + 20, (u8*)D);
		
		for (size_t j = 0; j < 5; ++j)
			OD[j] = D[j] ^ K[j]; // 'XOR' the data with the current digest

		std::copy((u8*)OD, (u8*)(OD + 5), outData + i);
		Crypto::sha1(outData + i, outData + i + 20, key);
		std::copy(key, key + 20, (u8*)K);
	}
}






SaveSlot::SaveSlot(void) : GC::SaveEditing::SaveSlot(0x1e000, 20) {
	initWithEmptyData(1);
}


SaveSlot::SaveSlot(const u8* inData, bool isDecrypted) : GC::SaveEditing::SaveSlot(0x1e000, 20, inData) {
	u32 flags = (isDecrypted) ? 1 : 0;
	load(flags);
}


SaveSlot::SaveSlot(SaveSlot const& other) : GC::SaveEditing::SaveSlot(other) {
	CP_ARRAY(checksum, 20);
}

void SaveSlot::deleteFields(void) {
	GC::SaveEditing::SaveSlot::deleteFields();
	_deleteFields_extension();
}

SaveSlot::~SaveSlot(void) {
	_deleteFields_extension();
}

SaveSlot* SaveSlot::clone(void) const {
	return new SaveSlot(*this);
}

SaveSlot* SaveSlot::create(void) const {
	return new SaveSlot;
}

void SaveSlot::swap(SaveSlot& other) {
	GC::SaveEditing::SaveSlot::swap(other);
	SW_ARRAY(checksum, 20);

}


bool SaveSlot::checkChecksum(bool fix){
	u8 newDigest[20];
	s32 hc_tmp = 0;
	LD_FIELD(s32, hc_tmp, 12);
	std::fill(data + 12, data + 16, 0); // headerChecksum field
	Crypto::sha1(data, data + 0x1dfd8, newDigest);
	SV_FIELD(s32, hc_tmp, 12);

	bool ret = std::equal(checksum, checksum + 20, newDigest);
	if (!ret && fix) std::copy(newDigest, newDigest + 20, checksum);
	return ret;
}

bool SaveSlot::checkHeaderChecksum(bool fix){
	using namespace IntegerManip::BE;
	u8 newDigest[20]; // when computing the header's checksum, words @0x18 @0x1c are already encrypted
	s32 hc_tmp = 0;
	LD_FIELD(s32, hc_tmp, 12);
	std::fill(data + 12, data + 16, 0); 
	Crypto::sha1(data, data + 0x1dfd8, newDigest);

	u32 D[2], H[2];
	u8 tmpBuf[8];
	
	std::copy(newDigest, newDigest + 8, (u8*)H);
	std::copy(data + 0x18, data + 0x20, (u8*)D);


	D[0] ^= ~H[0];
	D[1] ^= ~H[1];

	std::copy((u8*)D, (u8*)(D + 2), tmpBuf);

	s32 newHC = 0;
	for (size_t i = 0; i < 0x18; i += 4)
		newHC -= (s32) toInteger<u32, u8*>(data + i);

	newHC -= (s32)toInteger<u32,u8*>(tmpBuf);
	newHC -= (s32)toInteger<u32, u8*>(tmpBuf + 4);

	SV_FIELD(s32, hc_tmp, 12);

	bool ret = (newHC == gameConfig->headerChecksum);
	if (!ret && fix) gameConfig->headerChecksum = newHC;
	return ret;
}

std::pair<bool, bool> SaveSlot::checkBothChecksums(bool fixGlobalChecksum, bool fixHeaderChecksum) {
	if (!fixGlobalChecksum || !fixHeaderChecksum) return std::pair<bool, bool>(checkChecksum(fixGlobalChecksum), checkHeaderChecksum(fixHeaderChecksum));
	else {
		using namespace IntegerManip::BE;
		u8 newDigest[20]; // when computing the header's checksum, words @0x18 @0x1c are already encrypted
		s32 hc_tmp = 0;
		LD_FIELD(s32, hc_tmp, 12);
		std::fill(data + 12, data + 16, 0);
		Crypto::sha1(data, data + 0x1dfd8, newDigest);

		bool ret1 = std::equal(checksum, checksum + 20, newDigest);
		if (!ret1) std::copy(newDigest, newDigest + 20, checksum);

		u32 D[2], H[2];
		u8 tmpBuf[8];

		std::copy(newDigest, newDigest + 8, (u8*)H);
		std::copy(data + 0x18, data + 0x20, (u8*)D);


		D[0] ^= ~H[0];
		D[1] ^= ~H[1];

		std::copy((u8*)D, (u8*)(D + 2), tmpBuf);

		s32 newHC = 0;
		for (size_t i = 0; i < 0x18; i += 4)
			newHC -= (s32)toInteger<u32, u8*>(data + i);

		newHC -= (s32)toInteger<u32, u8*>(tmpBuf);
		newHC -= (s32)toInteger<u32, u8*>(tmpBuf + 4);

		SV_FIELD(s32, hc_tmp, 12);

		bool ret2 = (newHC == gameConfig->headerChecksum);
		gameConfig->headerChecksum = newHC;

		return std::pair<bool, bool>(ret1, ret2);
	}
}

bool SaveSlot::isCorrupt(void) {
	if ((static_cast<u32>(magic) & 0xffff0000) != (u32)ColosseumMagic) return true;
	std::pair<bool, bool> chk = checkBothChecksums();
	return !chk.first || !chk.second;
}


inline void doFixBugsAffectingPokemon(Pokemon* pkm) {
	// LibPkmGC <= 1.1.2 : For Pokémon Colosseum, IVs were loaded/saved as u8's where they were actually u16's. obedient was always set to true, and encounterType to a random value.

	std::copy(pkm->data + 0xa4, pkm->data + 0xa4 + 6, pkm->IVs);
	pkm->obedient = pkm->species == Mew || pkm->species == Deoxys;
	pkm->encounterType = 0;
}
void SaveSlot::fixBugsAffectingPokemon(void) {
	for (size_t i = 0; i < 6; ++i) 
		doFixBugsAffectingPokemon((Pokemon*)player->trainer->party[i]);

	for (size_t i = 0; i < 3; ++i) {
		for (size_t j = 0; j < 30; ++j)
			doFixBugsAffectingPokemon((Pokemon*)PC->boxes[i]->pkm[j]);
	}

	doFixBugsAffectingPokemon((Pokemon*)daycare->pkm);
}

void SaveSlot::loadData(u32 flags) {
	bool decrypted = (flags & 1) == 1;

	std::copy(data + 0x1dfec, data + 0x1e000, checksum);

	if (!decrypted) decrypt_in_place_impl(data, checksum);
}


void SaveSlot::loadFields(void) {
	randomBytes = new u8[20];
	LD_FIELD_E(u32, magic, 0, SaveMagic);
	LD_FIELD(s32, saveCount, 4);
	size_t offset = 8;


#define LD_IMPLEMENTED_SUBSTRUCTURE(type, field) LD_SUBSTRUCTURE(type, field, offset); offset += type::size;

	LD_IMPLEMENTED_SUBSTRUCTURE(GameConfigData, gameConfig);
	LD_IMPLEMENTED_SUBSTRUCTURE(PlayerData, player);
	LD_IMPLEMENTED_SUBSTRUCTURE(PCData, PC);
	LD_IMPLEMENTED_SUBSTRUCTURE(MailboxData, mailbox);
	LD_IMPLEMENTED_SUBSTRUCTURE(DaycareData, daycare);
	LD_IMPLEMENTED_SUBSTRUCTURE(StrategyMemoData, strategyMemo);
	offset += 0x523c;
	LD_IMPLEMENTED_SUBSTRUCTURE(BattleModeData, battleMode);
	// unknown substructures following

	std::copy(data + 0x1dfd8, data + 0x1dfec, randomBytes);
}

void SaveSlot::save(void) {
	magic = ColosseumMagic;
	SV_FIELD_E(u32, ColosseumMagic, 0, SaveMagic);
	SV_FIELD(u32, saveCount, 4);

	size_t offset = 8;


#define SV_IMPLEMENTED_SUBSTRUCTURE(type, field) SV_SUBSTRUCTURE(type, field, offset); offset += type::size;

	SV_IMPLEMENTED_SUBSTRUCTURE(GameConfigData, gameConfig);
	SV_IMPLEMENTED_SUBSTRUCTURE(PlayerData, player);
	SV_IMPLEMENTED_SUBSTRUCTURE(PCData, PC);
	SV_IMPLEMENTED_SUBSTRUCTURE(MailboxData, mailbox);
	SV_IMPLEMENTED_SUBSTRUCTURE(DaycareData, daycare);
	SV_IMPLEMENTED_SUBSTRUCTURE(StrategyMemoData, strategyMemo);
	offset += 0x523c;
	SV_IMPLEMENTED_SUBSTRUCTURE(BattleModeData, battleMode);
	// unknown substructures following


	checkBothChecksums(true, true); // update checksums
	offset = 8;
	SV_IMPLEMENTED_SUBSTRUCTURE(GameConfigData, gameConfig);

	std::copy(randomBytes, randomBytes + 20, data + 0x1dfd8);
	std::copy(checksum, checksum + 20, data + 0x1dfec);

}

void SaveSlot::saveEncrypted(u8* outBuf) {
	save();
	std::copy(data, data + 0x18, outBuf);
	std::copy(data + 0x1dfd8, data + 0x1e000, outBuf + 0x1dfd8);
	encrypt_impl(data, outBuf, checksum);
}

void SaveSlot::_deleteFields_extension(void) {
}

}
}
}
