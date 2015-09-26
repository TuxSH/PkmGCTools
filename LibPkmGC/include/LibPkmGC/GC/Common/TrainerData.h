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

#ifndef _LIBPKMGC_GC_TRAINER_DATA_H
#define _LIBPKMGC_GC_TRAINER_DATA_H

#include <LibPkmGC/GC/Common/Pokemon.h>


namespace LibPkmGC {

LIBPKMGC_FWD_DECL_GC_CLS(TrainerData)

namespace GC {

/*
For both Colosseum and XD:
	0x00 -- 0x2b: trainer name (10+1 wide characters) + copy
	0x2c: u16 SID
	0x2e: u16 TID
	0x30: Pokémon Party
*/
class LIBPKMGC_DECL TrainerData :
	public Base::DataStruct
{
public:
	TrainerData(size_t inSize, const u8* inData = NULL);
	virtual ~TrainerData(void);

	virtual TrainerData* clone(void) const = 0;
	virtual TrainerData* create(void) const = 0;

	virtual void swap(TrainerData& other);
	virtual TrainerData& operator=(TrainerData const& other);

	virtual void save(void);

	PokemonString* trainerName;
	u16 SID, TID;

	Pokemon* party[6];

protected:
	TrainerData(TrainerData const& other);

	virtual void deleteFields(void);
	virtual void loadFields(void);
};

}
}

#endif