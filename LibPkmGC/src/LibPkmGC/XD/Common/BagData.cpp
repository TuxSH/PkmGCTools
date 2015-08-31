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

#include <LibPkmGC/XD/Common/BagData.h>

namespace LibPkmGC {
namespace XD {

BagData::BagData(void) : GC::BagData(0x418, 30) {
	initWithEmptyData();
}

BagData::BagData(const u8* inData) : GC::BagData(0x418, 30, inData) {
	load();
}

BagData::BagData(BagData const& other) : GC::BagData(other) {
	CP_ARRAY(battleCDs, 60);
}


BagData::~BagData(){
}

void BagData::swap(BagData& other) {
	GC::BagData::swap(other);
	SW_ARRAY(battleCDs, 60);
}

BagData* BagData::clone(void) const {
	return new BagData(*this);
}

BagData* BagData::create(void) const {
	return new BagData;
}

void BagData::loadFields(void) {
	GC::BagData::loadFields();
	for (size_t i = 0; i < 60; ++i)
		battleCDs[i].load(data + 0x328 + 4 * i);
}

void BagData::save(void) {
	GC::BagData::save();
	for (size_t i = 0; i < 60; ++i)
		battleCDs[i].save(data + 0x328 + 4 * i);
}

}
}