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

#ifndef _LIBPKMGC_GC_PLAYER_DATA_H
#define _LIBPKMGC_GC_PLAYER_DATA_H

#include <LibPkmGC/GC/Common/TrainerData.h>
#include <LibPkmGC/GC/Common/BagData.h>

namespace LibPkmGC {

LIBPKMGC_FWD_DECL_GC_CLS(PlayerData)

namespace GC {

class LIBPKMGC_DECL PlayerData :
	public Base::DataStruct
{
public:
	PlayerData(size_t inSize, const u8* inData = NULL);
	virtual PlayerData& operator=(PlayerData const& other);

	virtual PlayerData* clone(void) const = 0;
	virtual PlayerData* create(void) const = 0;

	virtual ~PlayerData(void);

	virtual void swap(PlayerData& other);

	virtual void save(void);

	TrainerData* trainer;
	BagData* bag;

	Gender trainerGender;
	u32 pokeDollars;
	u32 pokeCoupons;
	
protected:
	PlayerData(PlayerData const& other);

	virtual void deleteFields(void);
};

}
}

#endif