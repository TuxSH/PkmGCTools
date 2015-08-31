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

#ifndef _LIBPKMGC_COLOSSEUM_GROUP_BATTLE_RULE_H
#define _LIBPKMGC_COLOSSEUM_GROUP_BATTLE_RULE_H

#include <LibPkmGC/GC/Common/GroupBattleRule.h>

namespace LibPkmGC {
namespace Colosseum {

class LIBPKMGC_DECL GroupBattleRule :
	public GC::GroupBattleRule
{
public:
	static const size_t size = 0x54;
	GroupBattleRule(const u8* inData);
	GroupBattleRule(GroupBattleRule const& other);
	GroupBattleRule(void);
	~GroupBattleRule();

//	void swap(GroupBattleRule& other);
	GroupBattleRule* clone(void) const;
	GroupBattleRule* create(void) const;

	void save(void);

protected:
	void loadFields(void);

private:
	GroupBattleRule(XD::GroupBattleRule const& other);

};

}
}

#endif