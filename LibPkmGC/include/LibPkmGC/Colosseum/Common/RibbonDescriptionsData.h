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

#ifndef _LIBPKMGC_COLOSSEUM_RIBBON_DESCRIPTION_DATA_H
#define _LIBPKMGC_COLOSSEUM_RIBBON_DESCRIPTION_DATA_H

#include <LibPkmGC/GC/Common/RibbonDescriptionsData.h>

namespace LibPkmGC {
namespace Colosseum {


class LIBPKMGC_DECL RibbonDescriptionsData :
	public GC::RibbonDescriptionsData
{
public:
	static const size_t size = 11;
	~RibbonDescriptionsData(void);
	RibbonDescriptionsData(void);
	RibbonDescriptionsData(const u8* inData);

	bool isXD(void) const;
	RibbonDescriptionsData* clone(void) const;
	RibbonDescriptionsData* create(void) const;

};

}
}

#endif