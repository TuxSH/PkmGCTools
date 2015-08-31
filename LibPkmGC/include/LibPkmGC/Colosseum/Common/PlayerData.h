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

#ifndef _LIBPKMGC_COLOSSEUM_PLAYER_DATA_H
#define _LIBPKMGC_COLOSSEUM_PLAYER_DATA_H

#include <LibPkmGC/GC/Common/PlayerData.h>
#include <LibPkmGC/Colosseum/Common/Pokemon.h>
#include <LibPkmGC/Colosseum/Common/BagData.h>

namespace LibPkmGC {
namespace Colosseum {

/*
	0x00 -- 0x2b: trainer name (10+1 chars) + copy
	0x2c: u16 SID
	0x2e: u16 TID
	0x30: Pokémon Party (6*0xc4)

	0x780: bag

	0xa80: u8 trainerGender
	0xa84: u32 money
	0xa88: u32 pkCoupons + copy
*/

class LIBPKMGC_DECL PlayerData :
	public GC::PlayerData
{
public:
	static const size_t size = 0xb18;
	PlayerData(void);
	PlayerData(PlayerData const& other);

	PlayerData(const u8* inData);


	~PlayerData(void);
	PlayerData* clone(void) const;
	PlayerData* create(void) const;

	void save(void);
protected:
	void loadFields(void);
private:
	PlayerData(XD::PlayerData const& other);
};

}
}

#endif
