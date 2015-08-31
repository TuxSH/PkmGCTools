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

#include <LibPkmGC/Colosseum/Common/GroupBattleRule.h>

namespace LibPkmGC {
namespace Colosseum {

GroupBattleRule::GroupBattleRule(const u8* inData) : GC::GroupBattleRule(0x54, 60, inData) {
	load();
}

GroupBattleRule::GroupBattleRule(void) : GC::GroupBattleRule(0x54, 60) {
	initWithEmptyData();
}

GroupBattleRule::GroupBattleRule(GroupBattleRule const& other) : GC::GroupBattleRule(other) {}

GroupBattleRule::~GroupBattleRule()
{
}


GroupBattleRule* GroupBattleRule::clone(void) const {
	return new GroupBattleRule(*this);
}

GroupBattleRule* GroupBattleRule::create(void) const {
	return new GroupBattleRule;
}

void GroupBattleRule::loadFields(void) {
	GC::GroupBattleRule::loadFields();
	LD_ARRAY_B(u8, bannedItems, 60, 24);
}

void GroupBattleRule::save(void) {
	GC::GroupBattleRule::save();
	SV_ARRAY_B(u8, bannedItems, 60, 24);
}

}
}