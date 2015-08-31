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

#ifndef _LIBPKMGC_GC_BAG_DATA_H
#define _LIBPKMGC_GC_BAG_DATA_H

#include <LibPkmGC/Core/ItemInfo.h>
#include <LibPkmGC/Base/DataStruct.h>

namespace LibPkmGC {

LIBPKMGC_FWD_DECL_GC_CLS(BagData)
namespace GC {

class LIBPKMGC_DECL BagData :
	public Base::DataStruct
{
public:
	BagData(size_t inSize, size_t nb_regular_items, const u8* inData = NULL);

	virtual ~BagData();

	virtual BagData* clone(void) const = 0;
	virtual BagData* create(void) const = 0;

	void swap(BagData& other);

	BagData& operator=(BagData const& other);

	virtual void save(void);

	const size_t nbRegularItems;
	Item* regularItems;
	Item keyItems[43];
	Item pokeballs[16];
	Item TMs[64];
	Item berries[46];
	Item colognes[3];

protected:
	BagData(BagData const& other);

	virtual void deleteFields(void);
	virtual void loadFields(void);
};

}
}

#endif