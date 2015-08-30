#include <LibPkmGC/GC/SaveEditing/SaveSlot.h>

namespace LibPkmGC {
namespace GC {
namespace SaveEditing {

SaveSlot::SaveSlot(size_t inSize, size_t nb_random_bytes, const u8* inData) : Base::DataStruct(inSize, inData), nbRandomBytes(nb_random_bytes) {
}

void SaveSlot::deleteFields(void) {
	delete[] randomBytes;
	delete player;
	delete PC;
	delete mailbox;
	delete daycare;
	delete strategyMemo;
	delete battleMode;
}

SaveSlot::~SaveSlot(void) {
	SaveSlot::deleteFields();
}

SaveSlot::SaveSlot(const SaveSlot& other) : Base::DataStruct(other),
magic(other.magic), headerChecksum(other.headerChecksum), saveCount(other.saveCount),
version(other.version), titleScreenLanguage(other.titleScreenLanguage), noRumble(other.noRumble), nbRandomBytes(other.nbRandomBytes){
	randomBytes = new u8[nbRandomBytes];
	std::copy(other.randomBytes, other.randomBytes + nbRandomBytes, randomBytes);

	std::copy(other.memcardUID, other.memcardUID + 2, memcardUID);

	CL(player);
	CL(PC);
	CL(mailbox);
	CL(daycare);
	CL(strategyMemo);

	CL(battleMode);

}


void SaveSlot::swap(SaveSlot& other) {
	if (nbRandomBytes != other.nbRandomBytes) throw std::invalid_argument("this->nbRandomBytes != other.nbRandomBytes");
	Base::DataStruct::swap(other);
	SW(magic);
	SW(headerChecksum);
	SW(saveCount);

	SW(memcardUID[0]); SW(memcardUID[1]);

	SW(version);
	SW(titleScreenLanguage);
	SW(noRumble);
	SW(player);
	SW(PC);
	SW(mailbox);
	SW(daycare);
	SW(strategyMemo);
	SW(battleMode);

	SW(randomBytes);
}

SaveSlot& SaveSlot::operator=(SaveSlot const& other) {
	if (nbRandomBytes != other.nbRandomBytes) throw std::invalid_argument("this->nbRandomBytes != other.nbRandomBytes");

	Base::DataStruct::operator=(other);
	if (this != &other) {
		SaveSlot::deleteFields();
		randomBytes = new u8[nbRandomBytes];
		CP_ARRAY(randomBytes, nbRandomBytes);
		CP(magic);
		CP(headerChecksum);
		CP(saveCount);
		CP(memcardUID[0]); CP(memcardUID[1]);

		CP(version);
		CP(titleScreenLanguage);
		CP(noRumble);


		CL(player);
		CL(PC);
		CL(mailbox);
		CL(daycare);
		CL(strategyMemo);
		CL(battleMode);
	}
	return *this;
}

void SaveSlot::reload(const u8* inData, u32 flags) {
	if (inData == NULL) Base::DataStruct::reload(NULL, 1);
	else Base::DataStruct::reload(inData, 0);
}


}
}
}