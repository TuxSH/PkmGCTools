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

#ifndef _LIBPKMGC_XD_PURIFICATION_CHAMBER_H
#define _LIBPKMGC_XD_PURIFICATION_CHAMBER_H

#include <LibPkmGC/XD/Common/Pokemon.h>
namespace LibPkmGC {
namespace XD {

/*
	0x00: XDPokemon normalPkm[4]
	0x310: XDPokemon shadowPkm
	0x3d4: u8 ??
	0x3d5 -- end: padding/trash bytes
*/

class LIBPKMGC_DECL PurificationChamber :
	public Base::DataStruct
{
public:
	static const size_t size = 0x3d8;
	PurificationChamber(void);
	PurificationChamber(const u8* inData);

	~PurificationChamber(void);

	PurificationChamber(PurificationChamber const& other);
	PurificationChamber& operator=(PurificationChamber const& other);
	void swap(PurificationChamber& other);

	PurificationChamber* clone(void) const;
	PurificationChamber* create(void) const;

	void save(void);

	Pokemon* normalPkm[4];
	Pokemon* shadowPkm;

private:
	void deleteFields(void);
	void loadFields(void);


};

}
}

#endif