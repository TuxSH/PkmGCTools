#include <LibPkmGC/XD/SaveEditing/Save.h>

namespace LibPkmGC {
namespace XD {
namespace SaveEditing {


Save::Save(void) : GC::SaveEditing::Save(0x56000, 2) {
	initWithEmptyData();
}

Save::Save(const u8* inData, bool hasGCIData_, bool isDecrypted) : GC::SaveEditing::Save(0x56000, 2, inData, hasGCIData_) {
	load((isDecrypted) ? 1 : 0);
}

Save::Save(Save const& other) : GC::SaveEditing::Save(other) {}

Save* Save::clone(void) const {
	return new Save(*this);
}

Save* Save::create(void) const {
	return new Save;
}

/*
	0x0000 -- 0x6000: save file title + icon (ignored here)
	0x6000: SaveSlot saveSlots[2]
*/
void Save::loadFields(void) {
	//	deleteFields();

	saveSlots = new GC::SaveEditing::SaveSlot*[2];
	u8* start = data + 0x6000;
	/*delete saveSlots[0];
	delete saveSlots[1];*/
	saveSlots[0] = new SaveSlot(start, _is_decrypted);
	saveSlots[1] = new SaveSlot(start + 0x28000, _is_decrypted);
}

void Save::save(void) {
	SV_SUBSTRUCTURE_ARRAY(SaveSlot, saveSlots, 2, 0x6000);
}

void Save::saveUnshuffled(void) {
	//nb_saveSlots = 2;
	for (size_t i = 0; i < 2; ++i) {
		SaveSlot* slot = (SaveSlot*)saveSlots[i];
		slot->saveUnshuffled();
	}

	u8* start = data + 0x6000;

	std::copy(saveSlots[0]->data, saveSlots[0]->data + 0x28000, start);
	std::copy(saveSlots[1]->data, saveSlots[1]->data + 0x28000, start + 0x28000);
}

}
}
}