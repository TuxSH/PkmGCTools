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

#ifndef _LIBPKMGC_COLO_POKEMON_H
#define _LIBPKMGC_COLO_POKEMON_H

#include <LibPkmGC/GC/Common/Pokemon.h>

namespace LibPkmGC {
namespace Colosseum {

/*
	0x00: u16 index
	0x02 : u16 ? ? ? ? (0 on shadow pkm)
	0x04 : u32 PID
	0x08 : VersionInfo version(4 bytes)
	0x0c : u16 locationCaught
	0x0e : u8 levelMet
	0x0f : u8 ballCaughtWith
	0x10 : u8 OTGender
	0x11 -- 0x13 : ? ? ? ? ?
	0x14 : u16 SID
	0x16 : u16 TID
	0x18 : OT Name(10 + 1 chars, limited to 8 in game)
	0x2e : Pkm Name(10 + 1, or 5 in game for jap.versions)
	0x44 : Pkm name backup
	0x5a -- 0x5b : u16 = field 0x02 backup
	0x5c : u32 experience
	0x60 : u8 currentLevel
	0x61 --  0x64 : ? ?
	0x65 -- 0x77: status info
	0x65 : u16 status
	0x69 : s8 turnsOfSleepRemaining
	0x6b : s8 turnsOfBadPoison
	0x74 : u32 = pokemonStatusToBitField(status, 0, turnsOfSleepRemaining)
	0x78 : moves info
	0x88 : u16 itemHeld
	0x8a : u16 currentHP
	0x8c : u16 stats[6]
	0x98 : u16 EVs[6]
	0xa4 : u16 IVs[6]
	0xb0 : u16 happinness
	0xb2 : u8 contestsStats[5]
	0xb7 : u8 contestsRibbons[5]
	0xbc : u8 contestLuster
	0xbd : u8 specialRibbons[12]
	0xc9 : u8 unimplentedRibbons (max. 15)
	0xca : u8 pokerusStatus
	0xcb : u8 flags[3] : egg, special ability, invalid pkm
	0xce : u8 GCUnk
	0xcf : u8 marks
	// shadow pkm data ?
	0xd0: s8 pokerusRemainingDays
	0xd1--0xd7 : ? ?
	0xd2: u16 unk2
	0xd4: u16 unk1
	0xd8 : u16 shadowPkmID
	0xda--0xdb : padding ?
	0xdc : s32 purificationCounter
	0xe0 : u32 expStored
	0xe4 : u16 ? ?
	0xe6 : u16 ? ?
	0xf8: u8 obedient
	0xfb : u8 encounterType
	0xfc--0x138 : ? ? ? ? ? ? ? ? ? ?
*/

class LIBPKMGC_DECL Pokemon : public GC::Pokemon {
public:
	static const size_t size = 0x138;
	Pokemon(void);
	Pokemon(const u8* inData);
	Pokemon(Pokemon const& other);
	~Pokemon(void);
	Pokemon* clone(void) const;
	Pokemon* create(void) const;

	void save(void);

	void swap(Pokemon& other);
	Pokemon& operator=(Pokemon const& other);

	Pokemon(GC::Pokemon const& other);
	Pokemon(Base::Pokemon const& other);
	Pokemon(XD::Pokemon const& other);
	Pokemon(GBA::Pokemon const& other);
	Pokemon& operator=(GC::Pokemon const& other);
	void swap(GC::Pokemon & other);
protected:
	void loadFields(void);

};


}
}

#endif