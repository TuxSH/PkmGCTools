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

#include <LibPkmGC/GC/Common/BattleModeData.h>

namespace LibPkmGC {
namespace GC {

BattleModeData::BattleModeData(size_t inSize, const u8* inData) : Base::DataStruct(inSize, inData) {
}

void BattleModeData::deleteFields(void) {
	for (size_t i = 0; i < 6; ++i) delete rules[i];
}

BattleModeData::~BattleModeData() {
	BattleModeData::deleteFields();
}

void BattleModeData::swap(BattleModeData& other) {
	Base::DataStruct::swap(other);
	for (size_t i = 0; i < 6; ++i) other.rules[i]->swap(*rules[i]);
}

BattleModeData::BattleModeData(BattleModeData const& other) : Base::DataStruct(other){
	CL_ARRAY(rules, 6);
}

BattleModeData & BattleModeData::operator=(BattleModeData const& other) {
	Base::DataStruct::operator=(other);
	if (this != &other) {
		CL_ARRAY(rules, 6);
	}
	return *this;
}

}
}