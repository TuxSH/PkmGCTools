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


#ifndef _LIBPKMGC_COLOSSEUM_SAVE_EDITING_SAVE_SLOT_H
#define _LIBPKMGC_COLOSSEUM_SAVE_EDITING_SAVE_SLOT_H

#include <LibPkmGC/GC/SaveEditing/SaveSlot.h>
#include <LibPkmGC/Colosseum/Common/Everything.h>

namespace LibPkmGC {
namespace Colosseum {
namespace SaveEditing {

/*
	size = 0x1e000
	0x00: u32 magic
	0x04: u32 saveCount
	0x08: **PARTIALLY UNENCRYPTED game config

	0x78: game config end

	0x78: other substructures. In Pokémon Colosseum, they are strictly contiguous with no trash bytes in between.

	(end)-40: **END OF ENCRYPTED DATA**

	(end)-40: u8 checksum[20]; // sha1 digest
	(end)-20: u8 randomBytes[20];
*/


class LIBPKMGC_DECL SaveSlot :
	public GC::SaveEditing::SaveSlot
{
public:
	static const size_t size = 0x1e000;
	SaveSlot(void);
	SaveSlot(const SaveSlot& other);

	SaveSlot(const u8* inData, bool isDecrypted = false);

	~SaveSlot(void);

	SaveSlot* clone(void) const;
	SaveSlot* create(void) const;

	void swap(SaveSlot& other);
	SaveSlot& operator=(SaveSlot const& other);

	void save(void);

	bool checkChecksum(bool fix = false);
	bool checkHeaderChecksum(bool fix = false);
	std::pair<bool, bool> checkBothChecksums(bool fixGlobalChecksum = false, bool fixHeaderChecksum = false);
	bool isCorrupt(void);

	void saveEncrypted(u8* outBuf);

	u8 checksum[20]; // digest

	void fixBugsAffectingPokemon(void); // LibPkmGC < 1.1.1
protected:
	void loadData(u32 flags = 0);
	void deleteFields(void);
	void loadFields(void);
private:
	void _deleteFields_extension(void);
	SaveSlot(XD::SaveEditing::SaveSlot const&);
};

}
}
}

#endif