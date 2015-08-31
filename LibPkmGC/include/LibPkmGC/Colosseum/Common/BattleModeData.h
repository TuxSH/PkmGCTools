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

#ifndef _LIBPKMGC_COLOSSEUM_BATTLE_MODE_DATA_H
#define _LIBPKMGC_COLOSSEUM_BATTLE_MODE_DATA_H

#include <LibPkmGC/GC/Common/BattleModeData.h>
#include <LibPkmGC/Colosseum/Common/GroupBattleRule.h>


namespace LibPkmGC {
namespace Colosseum {

/*
	??
	0xc16c: Colosseum::GroupBattleRules rules[26]
	??
*/
class LIBPKMGC_DECL BattleModeData :
	public GC::BattleModeData
{
public:
	static const size_t size = 0xcc2c;
	BattleModeData(void);
	BattleModeData(BattleModeData const& other);
	BattleModeData(const u8* inData);
	~BattleModeData();

	BattleModeData* clone(void) const;
	BattleModeData* create(void) const;

	void save(void);
protected:
	void loadFields(void);

private:
	BattleModeData(XD::BattleModeData const& other);

};

}
}

#endif