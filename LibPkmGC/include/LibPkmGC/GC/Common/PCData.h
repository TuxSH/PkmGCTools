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

#ifndef _LIBPKMGC_GC_PC_DATA_H
#define _LIBPKMGC_GC_PC_DATA_H

#include <LibPkmGC/GC/Common/PokemonBox.h>

namespace LibPkmGC {

LIBPKMGC_FWD_DECL_GC_CLS(PCData)
namespace GC {

class LIBPKMGC_DECL PCData :
	public Base::DataStruct
{
public:
	PCData(size_t inSize, size_t nb_boxes, const u8* inData = NULL);
	virtual ~PCData(void);

	virtual PCData* clone(void) const = 0;
	virtual PCData* create(void) const = 0;

	void swap(PCData& other);

	PCData& operator=(PCData const& other);

	PokemonBox** boxes;
	const size_t nbBoxes;

	Item items[235];

protected:
	PCData(PCData const& other);

	virtual void deleteFields(void);

};

}
}

#endif