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


#ifndef _LIBPKMGC_GC_SAVE_EDITING_SAVE_H
#define _LIBPKMGC_GC_SAVE_EDITING_SAVE_H

#include <LibPkmGC/GC/SaveEditing/SaveSlot.h>

namespace LibPkmGC {

namespace XD { namespace SaveEditing { class Save; } }
namespace Colosseum { namespace SaveEditing { class Save; } }

namespace GC {
namespace SaveEditing {

/*
For both Colosseum and XD:
	0x0000 -- 0x6000: banner data
	0x6000 -- end: SaveSlot saveSlots[3 (Colo.) or 2 (XD)]
*/

class LIBPKMGC_DECL Save :
	public Base::DataStruct
{
public:
	Save(size_t inSize, size_t  nb_slots, const u8* inData = NULL, bool hasGCIData_ = false);

	virtual Save* clone(void) const = 0;
	virtual Save* create(void) const = 0;

	void swap(Save& other);
	Save& operator=(Save const& other);

	virtual ~Save(void);

	virtual void reload(const u8* inData = NULL, u32 flags = 0);

	void saveEncrypted(u8* outBuf, bool exportGCIData = true);
	SaveSlot* getMostRecentSlot(size_t index = 0) const;
	SaveSlot* getMostRecentValidSlot(size_t index = 0, size_t *outIndex = NULL);

	SaveSlot** saveSlots;

	const size_t nbSlots;

	bool hasGCIData;
	u8 GCIData[0x40];

protected:
	Save(Save const& other);

	bool _is_decrypted;
	virtual void loadData(u32 flags = 0);
	virtual void deleteFields(void);

};

}
}
}

#endif