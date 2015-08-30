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


SaveSlot::SaveSlot(SaveSlot const& other) : GC::SaveEditing::SaveSlot(other), storyModeSaveCount(other.storyModeSaveCount) {
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
	SW(storyModeSaveCount);
	SW_ARRAY(checksum, 20);

}


bool SaveSlot::checkChecksum(bool fix){
	u8 newDigest[20];
	std::fill(data + 12, data + 16, 0); // headerChecksum field
	Crypto::sha1(data, data + 0x1dfd8, newDigest);
	SV_FIELD(s32, headerChecksum, 12);

	bool ret = std::equal(checksum, checksum + 20, newDigest);
	if (!ret && fix) std::copy(newDigest, newDigest + 20, checksum);
	return ret;
}

bool SaveSlot::checkHeaderChecksum(bool fix){
	using namespace IntegerManip::BE;
	u8 newDigest[20]; // when computing the header's checksum, words @0x18 @0x1c are already encrypted
	std::fill(data + 12, data + 16, 0); // headerChecksum field
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

	SV_FIELD(s32, headerChecksum, 12);

	bool ret = (newHC == headerChecksum);
	if (!ret && fix) headerChecksum = newHC;
	return ret;
}

std::pair<bool, bool> SaveSlot::checkBothChecksums(bool fixGlobalChecksum, bool fixHeaderChecksum) {
	if (!fixGlobalChecksum || !fixHeaderChecksum) return std::pair<bool, bool>(checkChecksum(fixGlobalChecksum), checkHeaderChecksum(fixHeaderChecksum));
	else {
		using namespace IntegerManip::BE;
		u8 newDigest[20]; // when computing the header's checksum, words @0x18 @0x1c are already encrypted
		std::fill(data + 12, data + 16, 0); // headerChecksum field
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

		SV_FIELD(s32, headerChecksum, 12);

		bool ret2 = (newHC == headerChecksum);
		headerChecksum = newHC;

		return std::pair<bool, bool>(ret1, ret2);
	}
}

bool SaveSlot::isCorrupt(void) {
	if ((static_cast<u32>(magic) & 0xffff0000) != (u32)ColosseumMagic) return true;
	std::pair<bool, bool> chk = checkBothChecksums();
	return !chk.first || !chk.second;
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

	version.load(data + 8);
	LD_FIELD(u32, headerChecksum, 12);
	LD_ARRAY(u32, memcardUID, 2, 16);
	LD_FIELD(u32, storyModeSaveCount, 24);
	
	LD_FIELD_B(u8, noRumble, 0x31);
	LD_FIELD_E(u16, titleScreenLanguage, 0x32, LanguageIndex);
	size_t offset = 0x70 + 8;


#define LD_IMPLEMENTED_SUBSTRUCTURE(type, field) LD_SUBSTRUCTURE(type, field, offset); offset += type::size;

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
	//deleteFields();

	version.save(data + 8);
	SV_ARRAY(u32, memcardUID, 2, 16);
	SV_FIELD(s32, storyModeSaveCount, 24);
	SV_FIELD_B(u8, noRumble, 0x31);
	SV_FIELD_E(u16, titleScreenLanguage, 0x32, LanguageIndex);
	
	size_t offset = 0x70 + 8;


#define SV_IMPLEMENTED_SUBSTRUCTURE(type, field) SV_SUBSTRUCTURE(type, field, offset); offset += type::size;

	SV_IMPLEMENTED_SUBSTRUCTURE(PlayerData, player);
	SV_IMPLEMENTED_SUBSTRUCTURE(PCData, PC);
	SV_IMPLEMENTED_SUBSTRUCTURE(MailboxData, mailbox);
	SV_IMPLEMENTED_SUBSTRUCTURE(DaycareData, daycare);
	SV_IMPLEMENTED_SUBSTRUCTURE(StrategyMemoData, strategyMemo);
	offset += 0x523c;
	SV_IMPLEMENTED_SUBSTRUCTURE(BattleModeData, battleMode);
	// unknown substructures following


	checkBothChecksums(true, true); // update checksums
	SV_FIELD(u32, headerChecksum, 12);

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
