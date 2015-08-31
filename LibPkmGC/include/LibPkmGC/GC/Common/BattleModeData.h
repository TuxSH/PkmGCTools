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

#ifndef _LIBPKMGC_GC_BATTLE_MODE_DATA_H
#define _LIBPKMGC_GC_BATTLE_MODE_DATA_H

#include <LibPkmGC/GC/Common/GroupBattleRule.h>

namespace LibPkmGC {

LIBPKMGC_FWD_DECL_GC_CLS(BattleModeData)

namespace GC {

class LIBPKMGC_DECL BattleModeData :
	public Base::DataStruct
{
public:
	BattleModeData(size_t inSize, const u8* inData = NULL);

	virtual ~BattleModeData();

	virtual BattleModeData* clone(void) const = 0;
	virtual BattleModeData* create(void) const = 0;

	void swap(BattleModeData& other);
	BattleModeData& operator=(BattleModeData const& other);

	GroupBattleRule* rules[6];

protected:
	BattleModeData(BattleModeData const& other);

	virtual void deleteFields(void);

};

}
}

#endif