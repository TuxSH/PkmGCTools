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