#include <LibPkmGC/Colosseum/SaveEditing/Save.h>

namespace LibPkmGC {
namespace Colosseum {
namespace SaveEditing {


Save::Save(void) : GC::SaveEditing::Save(0x60000, 3) {
	initWithEmptyData();
}

Save::Save(const u8* inData, bool hasGCIData_, bool isDecrypted) : GC::SaveEditing::Save(0x60000, 3, inData, hasGCIData_) {
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
	0x6000: SaveSlot saveSlots[3]
*/
void Save::loadFields(void) {
	//	deleteFields();

	saveSlots = new GC::SaveEditing::SaveSlot*[3];
	u8* start = data + 0x6000;
	/*delete saveSlots[0];
	delete saveSlots[1];*/
	saveSlots[0] = new SaveSlot(start, _is_decrypted);
	saveSlots[1] = new SaveSlot(start + 0x1e000, _is_decrypted);
	saveSlots[2] = new SaveSlot(start + 0x1e000*2, _is_decrypted);

}

void Save::save(void) {
	SV_SUBSTRUCTURE_ARRAY(SaveSlot, saveSlots, 3, 0x6000);
}


}
}
}