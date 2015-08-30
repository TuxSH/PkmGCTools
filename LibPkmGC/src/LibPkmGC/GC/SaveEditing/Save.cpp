#include <LibPkmGC/GC/SaveEditing/Save.h>

namespace LibPkmGC {
namespace GC {
namespace SaveEditing {

Save::Save(size_t inSize, size_t nb_slots, const u8* inData, bool hasGCIData_) : Base::DataStruct(inSize, inData + ((hasGCIData_ && inData != NULL) ? 0x40 : 0)),
hasGCIData(hasGCIData_), nbSlots(nb_slots) {
	if (hasGCIData) std::copy(inData, inData + 0x40, GCIData);
}


void Save::deleteFields(void) {
	for (size_t i = 0; i < nbSlots; ++i)
		delete saveSlots[i];

	delete[] saveSlots;
}


Save::~Save(void) {
	Save::deleteFields();
}

void Save::swap(Save& other) {
	if (nbSlots != other.nbSlots) throw std::invalid_argument("this->nbSlots != other.nbSlots");
	Base::DataStruct::swap(other);
	SW(saveSlots);
	SW(_is_decrypted);
	SW(hasGCIData);
	SW_ARRAY(GCIData, 0x40);
}

Save::Save(Save const& other) : Base::DataStruct(other), nbSlots(other.nbSlots), _is_decrypted(other._is_decrypted), hasGCIData(other.hasGCIData) {
	saveSlots = new SaveSlot*[nbSlots];
	CL_ARRAY(saveSlots, nbSlots);
	CP_ARRAY(GCIData, 64);
}

Save& Save::operator=(Save const& other) {
	if (nbSlots != other.nbSlots) throw std::invalid_argument("this->nbSlots != other.nbSlots");
	Base::DataStruct::operator=(other);
	if (this != &other) {
		Save::deleteFields();

		CP(_is_decrypted);
		CP(hasGCIData);
		CP_ARRAY(GCIData, 64);

		saveSlots = new SaveSlot*[nbSlots];
		for (size_t i = 0; i < nbSlots; ++i)
			saveSlots[i] = other.saveSlots[i]->clone();
	}

	return *this;
}

void Save::loadData(u32 flags) {
	_is_decrypted = ((flags & 1) == 1) ? true : false;
}

void Save::reload(const u8* inData, u32 flags) {
	if (inData == NULL) Base::DataStruct::reload(NULL, 1);
	else Base::DataStruct::reload(inData, 0);
}

void Save::saveEncrypted(u8* outBuf, bool exportGCIData) {
	if (hasGCIData && exportGCIData) {
		std::copy(GCIData, GCIData + 0x40, outBuf);
		outBuf += 0x40;
	}
	std::copy(data, data + 0x6000, outBuf);
	size_t sz = saveSlots[0]->fixedSize;
	for (size_t i = 0; i < nbSlots; ++i)
		saveSlots[i]->saveEncrypted(outBuf + 0x6000 + sz*i);
}

inline bool date_comparison(SaveSlot* a, SaveSlot* b) {
	return (a->saveCount > b->saveCount); // order by saveCount desc
}

SaveSlot* Save::getMostRecentSlot(size_t index) const {
	if (index > nbSlots) return NULL;
	SaveSlot** slots2 = new SaveSlot*[nbSlots];
	std::copy(saveSlots, saveSlots + nbSlots, slots2);
	std::sort(slots2, slots2 + nbSlots, date_comparison);

	SaveSlot* ret = slots2[index];
	delete[] slots2;
	return ret;
}

SaveSlot * Save::getMostRecentValidSlot(size_t index, size_t *outIndex) {
	if (index > nbSlots) return NULL;
	SaveSlot** slots2 = new SaveSlot*[nbSlots];
	std::copy(saveSlots, saveSlots + nbSlots, slots2);
	std::sort(slots2, slots2 + nbSlots, date_comparison);

	size_t v = 0;
	while (v < nbSlots && slots2[v]->isCorrupt()) ++v;
	if (outIndex != NULL) *outIndex = v;
	if (v == nbSlots) {
		delete[] slots2;
		return NULL;
	}
	SaveSlot* ret = slots2[index];
	delete[] slots2;
	return ret;
}

}
}
}