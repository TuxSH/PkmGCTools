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

#ifndef _LIBPKMGC_GC_RIBBON_DESCRIPTION_DATA_H
#define _LIBPKMGC_GC_RIBBON_DESCRIPTION_DATA_H

#include <LibPkmGC/Base/DataStruct.h>

namespace LibPkmGC {

LIBPKMGC_FWD_DECL_GC_CLS(RibbonDescriptionsData)

namespace GC {

/*
	This is just an array of description IDs :
		u8 descriptions[11];
	Concerned ribbons: Marine, Land, Sky, Country, National, Earth, World, Unused 1,2,3,4

	Please refer to Core/Detail/RibbonDescriptions.cpp
*/

class LIBPKMGC_DECL RibbonDescriptionsData :
	public Base::DataStruct
{
public:
	RibbonDescriptionsData(const u8* inData = NULL);
	virtual ~RibbonDescriptionsData(void);
	virtual bool isXD(void) const = 0;
	virtual void save(void);

	virtual RibbonDescriptionsData* clone(void) const = 0;
	virtual RibbonDescriptionsData* create(void) const = 0;

	void swap(RibbonDescriptionsData& other);

	u8 descriptions[11];

protected:
	virtual void deleteFields(void);
	virtual void loadFields(void);
};

}
}

#endif