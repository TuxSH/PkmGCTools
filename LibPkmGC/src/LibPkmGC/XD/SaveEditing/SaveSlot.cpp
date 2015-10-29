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

#define _SCL_SECURE_NO_WARNINGS
#include <LibPkmGC/XD/SaveEditing/SaveSlot.h>

namespace LibPkmGC {
namespace XD {
namespace SaveEditing {


static const s8 substructureOrder[16] = { 0,1,2,3,4,5,6,7,8,9,-1,-1,-1,-1,15,14 };
static const u16 substructureMaxSizes[16] = /* default sizes */
{
 0x88, 0x978, 0xbc50, 0x4a, 0xcc, 0x1774,
 0x364, 0x2400, 0x6b4, 0xb, 0x400, 0x800, 0x1000, 0x2000,
 0x2298, 0xc800
};
static const u16 substructureOffsetIncrements[16] =
{
 0xa0, 0x990, 0xbc60, 0x60, 0xe0, 0x1790,
 0x380, 0x2410, 0x6d0, 0x20, 0x410, 0x810,
 0x1010, 0x2010, 0x22b0, 0xc810
};

inline void advanceKeys(u16 keys[4]) {
	u16 a = keys[0] + 0x43, b = keys[1] + 0x29, c = keys[2] + 0x17, d = keys[3] + 0x13;

	keys[0] = (a & 0xf) | ((b << 4) & 0xf0) | ((c << 8) & 0xf00) | ((d << 12) & 0xf000);
	keys[1] = ((a >> 4) & 0xf) | (b & 0xf0) | ((c << 4) & 0xf00) | ((d << 8) & 0xf000);
	keys[2] = (c & 0xf00) | ((b & 0xf00) >> 4) | ((a & 0xf00) >> 8) | ((d << 4) & 0xf000);
	keys[3] = ((a >> 12) & 0xf) | ((b >> 8) & 0xf0) | ((c >> 4) & 0xf00) | (d & 0xf000);
}

inline void decrypt_impl(u8* in, u8* out, u16 encryptionKeys[4]) { //the encryption algorithm isn't really strong, isn't it?
	using namespace IntegerManip::BE;
	u32 end = 0x27fd8;
	u16 keys[4] = { 0 };
	std::copy(encryptionKeys, encryptionKeys + 4, keys);
	u16 tmp = 0;

	for (size_t i = 16; i < end; i += 8) {
		for (size_t j = 0; j < 4; ++j) {
			tmp = toInteger<u16, u8*>(in + i + 2 * j, 2);
			tmp -= keys[j];
			fromInteger<u16, u8*>(out + i + 2 * j, tmp, 2);
		}
		advanceKeys(keys);
	}
}

inline void encrypt_impl(u8* in, u8* out, const u16 encryptionKeys[4], u32 end = 0x27fd8) {
	using namespace IntegerManip::BE;

	u16 keys[4] = { 0 };
	std::copy(encryptionKeys, encryptionKeys + 4, keys);
	u16 tmp = 0;

	for (size_t i = 16; i < end; i += 8) {
		for (size_t j = 0; j < 4; ++j) {
			tmp = toInteger<u16, u8*>(in + i + 2 * j, 2);
			tmp += keys[j];
			fromInteger<u16, u8*>(out + i + 2 * j, tmp, 2);
		}
		advanceKeys(keys);
	}
}




SaveSlot::SaveSlot(void) : GC::SaveEditing::SaveSlot(0x28000, 40) {
	initWithEmptyData(1);
}


SaveSlot::SaveSlot(const u8* inData, bool isDecrypted) : GC::SaveEditing::SaveSlot(0x28000, 40, inData) {
	u32 flags = (isDecrypted) ? 1 : 0;
	load(flags);
}

SaveSlot::SaveSlot(SaveSlot const& other) : GC::SaveEditing::SaveSlot(other) {
	CP_ARRAY(checksum, 4);
	CP_ARRAY(encryptionKeys, 4);
	CP_ARRAY(substructureOffsets, 16);



	CL(purifier);

	CP(_other_corruption_flags);
	for (size_t i = 0; i < 16; ++i) {
		if (other.unhandledSubstructures[i] != NULL) unhandledSubstructures[i] = other.unhandledSubstructures[i]->clone();
		else unhandledSubstructures[i] = NULL;
	}
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
	SW_ARRAY(encryptionKeys, 4);
	SW_ARRAY(checksum, 4);

	SW_ARRAY(substructureSizes, 16);
	SW_ARRAY(substructureOffsets, 16);
	SW_ARRAY(flagDataSubSizes, 5);
	
	SW_ARRAY(unhandledSubstructures, 16);

	SW(purifier);
}

SaveSlot& SaveSlot::operator=(SaveSlot const & other) {
	GC::SaveEditing::SaveSlot::operator=(other);
	if (this != &other) {
		CP_ARRAY(checksum, 4);
		CP_ARRAY(encryptionKeys, 4);
		CP_ARRAY(substructureSizes, 16);
		CP_ARRAY(substructureOffsets, 16);
		CP_ARRAY(flagDataSubSizes, 5);
		for (size_t i = 0; i < 16; ++i) {
			if (other.unhandledSubstructures[i] != NULL) unhandledSubstructures[i] = other.unhandledSubstructures[i]->clone();
			else unhandledSubstructures[i] = NULL;
		}
		CL(purifier);
	}
	return *this;
}

void SaveSlot::swap(GC::SaveEditing::SaveSlot& other) {
	if (LIBPKMGC_IS_XD(SaveEditing::SaveSlot, &other))
		swap((SaveSlot&)other);
	else
		GC::SaveEditing::SaveSlot::swap(other);
}

SaveSlot& SaveSlot::operator=(GC::SaveEditing::SaveSlot const& other) {
	if (LIBPKMGC_IS_XD(SaveEditing::SaveSlot, &other))
		operator=((SaveSlot const&)other);
	else
		GC::SaveEditing::SaveSlot::operator=(other);
	return *this;
}

void SaveSlot::loadData(u32 flags) {
	bool decrypted = (flags & 1) == 1;

	LD_ARRAY(u16, encryptionKeys, 4, 8);

	if (!decrypted) decrypt_impl(data, data, encryptionKeys);
}

template<typename cls> cls* loadSubstructure(u8* data, u32 offset, u32 sz, u32 maxSize) {
	if (offset + 0xa8 >= 0x28000) return new cls;

	if (sz < maxSize) {
		u8* dt = new u8[maxSize];
		std::fill(dt, dt + maxSize, 0);
		std::copy(data + 0xa8 + offset, data + 0xa8 + offset + sz, dt);
		cls* ret = new cls(dt);
		delete[] dt;
		return ret;
	}
	else {
		return new cls(data + 0xa8 + offset);
	}
}

template<> Base::UnimplementedStruct* loadSubstructure<Base::UnimplementedStruct>(u8* data, u32 offset, u32 sz, u32 maxSize) {
	typedef Base::UnimplementedStruct cls;

	if (offset + 0xa8 >= 0x28000) return new cls(maxSize);

	if (sz < maxSize) {
		u8* dt = new u8[maxSize];
		std::fill(dt, dt + maxSize, 0);
		std::copy(data + 0xa8 + offset, data + 0xa8 + offset + sz, dt);
		cls* ret = new cls(maxSize, dt);
		delete[] dt;
		return ret;
	}
	else {
		return new cls(maxSize, data + 0xa8 + offset);
	}
}

void SaveSlot::loadFields(void) {
	randomBytes = new u8[40];
	LD_FIELD_E(u32, magic, 0, SaveMagic);
	LD_FIELD(s32, saveCount, 4);
	u16 checksum_tmp[8];
	LD_ARRAY(u16, checksum_tmp, 8, 0x10);

	std::reverse(checksum_tmp, checksum_tmp + 8);

	for (size_t i = 0; i < 4; ++i)
		checksum[i] = ((u32)checksum_tmp[2 * i] << 16) | (u32)checksum_tmp[2 * i + 1];


	u16 substructureOffsetsTmp[32]; // the upper 16 bits of each offset are stored AFTER the lower ones
	LD_ARRAY(u16, substructureSizes, 16, 0x20);
	LD_ARRAY(u16, substructureOffsetsTmp, 32, 0x40);
	LD_ARRAY(u16, flagDataSubSizes, 4, 0x80);
	LD_FIELD(u16, flagDataSubSizes[4], 0x8a);

	u8* start = data + 8 + 0xa0;
	for (size_t i = 0; i < 16; ++i)
		substructureOffsets[i] = (substructureOffsetsTmp[2 * i + 1] << 16) | substructureOffsetsTmp[2 * i];

	_other_corruption_flags = substructureSizes[0] != 0x88;
	for (size_t i = 0; i < 16; ++i) {
		if (i <= 6 || i == 9 || i == 14) {
			unhandledSubstructures[i] = NULL;
			continue;
		}

		unhandledSubstructures[i] =  loadSubstructure<Base::UnimplementedStruct>(data, substructureOffsets[i], substructureSizes[i], substructureMaxSizes[i]);

	}

#define LD_IMPLEMENTED_SUBSTRUCTURE(type, field, id) field = loadSubstructure<type>(data, substructureOffsets[id], substructureSizes[id], substructureMaxSizes[id])

	LD_IMPLEMENTED_SUBSTRUCTURE(GameConfigData, gameConfig, 0);
	LD_IMPLEMENTED_SUBSTRUCTURE(PlayerData, player, 1);
	LD_IMPLEMENTED_SUBSTRUCTURE(PCData, PC, 2);
	LD_IMPLEMENTED_SUBSTRUCTURE(MailboxData, mailbox, 3);
	LD_IMPLEMENTED_SUBSTRUCTURE(DaycareData, daycare, 4);
	LD_IMPLEMENTED_SUBSTRUCTURE(StrategyMemoData, strategyMemo, 5);
	LD_IMPLEMENTED_SUBSTRUCTURE(BattleModeData, battleMode, 6);
	LD_IMPLEMENTED_SUBSTRUCTURE(RibbonDescriptionsData, ribbonDescriptions, 9);
	LD_IMPLEMENTED_SUBSTRUCTURE(PurifierData, purifier, 14);

	{ // flags
		u16 sz = 0;
		for (size_t i = 0; i < 5; ++i) sz += flagDataSubSizes[i];
		if (sz <= substructureMaxSizes[8] && substructureSizes[8] == substructureMaxSizes[8])
			std::fill(unhandledSubstructures[8]->data + sz, unhandledSubstructures[8]->data + substructureMaxSizes[8], 0);
	}

	std::copy(substructureMaxSizes, substructureMaxSizes + 16, substructureSizes);
	std::copy(data + size - 40, data + size, randomBytes);
}

bool SaveSlot::checkChecksum(bool fix) {
	using namespace IntegerManip::BE;
	u32 new_checksum[4] = { 0 };

	u8 tmpbuf[0x10];
	std::copy(data + 0x10, data + 0x20, tmpbuf);
	std::fill(data + 0x10, data + 0x20, 0);

	u8* dt = data + 0x08;

	for (size_t i = 0; i < 4; ++i) {
		for (size_t j = 0; j < 0x9ff4; j += 2) {
			new_checksum[i] += (u32)toInteger<u16, u8*>(dt, 2);
			dt += 2;
		}
	}

	bool ret = std::equal(checksum, checksum + 4, new_checksum);

	if (!ret && fix) std::copy(new_checksum, new_checksum + 4, checksum);

	std::copy(tmpbuf, tmpbuf + 0x10, data + 0x10);
	return ret;
}

bool SaveSlot::checkHeaderChecksum(bool fix) {
	s32 new_header_checksum = 0;
	for (size_t i = 0; i < 8; ++i) new_header_checksum += (s32)(u32)data[i];

	bool ret = new_header_checksum == gameConfig->headerChecksum;
	if (!ret && fix) gameConfig->headerChecksum = new_header_checksum;

	return ret;
}

std::pair<bool, bool> SaveSlot::checkBothChecksums(bool fixGlobalChecksum, bool fixHeaderChecksum) {
	if (!fixGlobalChecksum || !fixHeaderChecksum) return std::pair<bool, bool>(checkChecksum(fixGlobalChecksum), checkHeaderChecksum(fixHeaderChecksum));
	else {
		bool first, second;
		s32 oldHC = gameConfig->headerChecksum;
		first = checkHeaderChecksum(true);
		SV_FIELD(s32, gameConfig->headerChecksum, 0xa8 + substructureOffsets[0] + 0x38);
		second = checkChecksum(true);
		SV_FIELD(s32, oldHC, 0xa8 + substructureOffsets[0] + 0x38);
		return std::pair<bool, bool>(first, second);
	}
}

bool SaveSlot::isCorrupt(void) {
	if (((static_cast<u32>(magic) & 0xffffff00) != (u32)XDMagic) || _other_corruption_flags) return true; // substructureSizes[0] != 0x88;
	std::pair<bool, bool> chk = checkBothChecksums();
	return !chk.first || !chk.second;
}

void SaveSlot::save_impl(bool saveAll) {
	magic = XDMagic;

	u8* start = data + 8 + 0xa0;

	SV_FIELD_E(u32, XDMagic, 0, SaveMagic);
	SV_FIELD(s32, saveCount, 4);
	SV_ARRAY(u16, encryptionKeys, 4, 8);

	std::copy(randomBytes, randomBytes + 40, data + size - 40);


	if(saveAll) std::fill(start, data + size - 40, 0); // clean the filler bytes

	std::copy(substructureMaxSizes, substructureMaxSizes + 16, substructureSizes);


	{ // flags
		u16 sz = 0;
		for (size_t i = 0; i < 5; ++i) sz += flagDataSubSizes[i];
		if (sz <= substructureMaxSizes[8])
			std::fill(unhandledSubstructures[8]->data + sz, unhandledSubstructures[8]->data + substructureMaxSizes[8], 0);
	}

	for (size_t i = 0; i < 16; ++i) {
		if (unhandledSubstructures[i] == NULL) continue;
		else if (substructureOrder[i] == -1) std::fill(unhandledSubstructures[i]->data, unhandledSubstructures[i]->data + substructureMaxSizes[i], 0); // 100% trash data
		std::copy(unhandledSubstructures[i]->data, unhandledSubstructures[i]->data + substructureMaxSizes[i], start + substructureOffsets[i]);
	}

#define SV_IMPLEMENTED_SUBSTRUCTURE(type, field, id) field->save(); std::copy(field->data, field->data + substructureMaxSizes[id], start + substructureOffsets[id]);

	SV_IMPLEMENTED_SUBSTRUCTURE(GameConfigData, gameConfig, 0);

	if (saveAll) {
		SV_IMPLEMENTED_SUBSTRUCTURE(PlayerData, player, 1);
		SV_IMPLEMENTED_SUBSTRUCTURE(PCData, PC, 2);
		SV_IMPLEMENTED_SUBSTRUCTURE(MailboxData, mailbox, 3);
		SV_IMPLEMENTED_SUBSTRUCTURE(DaycareData, daycare, 4);
		SV_IMPLEMENTED_SUBSTRUCTURE(StrategyMemoData, strategyMemo, 5);
		SV_IMPLEMENTED_SUBSTRUCTURE(BattleModeData, battleMode, 6);
		SV_IMPLEMENTED_SUBSTRUCTURE(RibbonDescriptionsData, ribbonDescriptions, 9);
		SV_IMPLEMENTED_SUBSTRUCTURE(PurifierData, purifier, 14);
	}

	u16 substructureOffsetsTmp[32]; // the upper 16 bits of each offset are stored AFTER the lower ones
	std::copy(substructureMaxSizes, substructureMaxSizes + 16, substructureSizes);
	SV_ARRAY(u16, substructureSizes, 16, 0x20);
	_other_corruption_flags = false;


	for (size_t i = 0; i < 16; ++i) {
		substructureOffsetsTmp[2 * i] = (u16)substructureOffsets[i];
		substructureOffsetsTmp[2 * i + 1] = (u16)(substructureOffsets[i] >> 16);
	}

	SV_ARRAY(u16, substructureOffsetsTmp, 32, 0x40);
	SV_ARRAY(u16, flagDataSubSizes, 4, 0x80);
	SV_FIELD(u16, flagDataSubSizes[4], 0x8a);


	checkBothChecksums(true);
	SV_IMPLEMENTED_SUBSTRUCTURE(GameConfigData, gameConfig, 0);

	u16 checksum_tmp[8];

	for (size_t i = 0; i < 4; ++i) {
		checksum_tmp[2 * i] = (u16)(checksum[i] >> 16);
		checksum_tmp[2 * i + 1] = (u16)checksum[i];
	}
	std::reverse(checksum_tmp, checksum_tmp + 8);
	SV_ARRAY(u16, checksum_tmp, 8, 0x10);

}


void SaveSlot::reorderSubstructures(void) {
	u32 offset = 0;
	for (size_t i = 0; i < 16; ++i) {
		s8 subscript = substructureOrder[i];
		if (subscript == -1) continue;
		substructureOffsets[(size_t)subscript] = offset;
		offset += substructureOffsetIncrements[(size_t)subscript];
	}

	for (size_t i = 10; i < 14; ++i) {
		substructureOffsets[i] = offset;
		offset += substructureOffsetIncrements[i];
	}
}

void SaveSlot::saveUnshuffled(void) {
	reorderSubstructures();
	save();
}

void SaveSlot::saveEncrypted(u8* outBuf, bool saveAll) {
	save_impl(saveAll);
	std::copy(data, data + 0x10, outBuf);
	std::copy(data + 0x28000 - 40, data + 0x28000, outBuf + 0x28000 - 40);
	encrypt_impl(data, outBuf, encryptionKeys);
}

void SaveSlot::_deleteFields_extension(void) {
	for (size_t i = 0; i < 16; ++i) delete unhandledSubstructures[i];
	delete purifier;
}

}
}
}