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

#ifndef _LIBPKMGC_PURIFIER_DATA_H
#define _LIBPKMGC_PURIFIER_DATA_H

#include <LibPkmGC/XD/Common/PurificationChamber.h>

namespace LibPkmGC {
namespace XD {

/*
	0x00--end(0x2298): PurificationChamber chambers[9]
*/

class LIBPKMGC_DECL PurifierData :
	public Base::DataStruct
{
public:
	static const size_t size = 0x2298;
	PurifierData(void);
	PurifierData(const u8* inData);

	~PurifierData(void);

	PurifierData(PurifierData const& other);
	PurifierData& operator=(PurifierData const& other);
	void swap(PurifierData& other);

	PurifierData* clone(void) const;
	PurifierData* create(void) const;

	void save(void);

	PurificationChamber* chambers[9];

private:
	void deleteFields(void);
	void loadFields(void);

};

}
}

#endif