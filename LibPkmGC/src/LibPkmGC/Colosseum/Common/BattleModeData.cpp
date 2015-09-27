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

#include <LibPkmGC/Colosseum/Common/BattleModeData.h>

namespace LibPkmGC {
namespace Colosseum {

BattleModeData::BattleModeData(void) : GC::BattleModeData(0xcc2c) {
	initWithEmptyData();
}

BattleModeData::BattleModeData(const u8* inData) : GC::BattleModeData(0xcc2c, inData) {
	load();
}

BattleModeData::BattleModeData(BattleModeData const& other) : GC::BattleModeData(other) {}


BattleModeData::~BattleModeData()
{
}

BattleModeData* BattleModeData::clone(void) const
{
	return new BattleModeData(*this);
}

BattleModeData* BattleModeData::create(void) const
{
	return new BattleModeData;
}

void BattleModeData::loadFields(void) {
	LD_SUBSTRUCTURE_ARRAY(GroupBattleRule, rules, 6, 0xc9dc);
}

void BattleModeData::save(void) {
	SV_SUBSTRUCTURE_ARRAY(GroupBattleRule, rules, 6, 0xc9dc);
}

}
}