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

#include <LibPkmGC/XD/Common/DaycareData.h>


namespace LibPkmGC {
namespace XD {

DaycareData::DaycareData(void) : GC::DaycareData(0xcc) {
	initWithEmptyData();
}

DaycareData::DaycareData(const u8* inData) : GC::DaycareData(0xcc, inData) {
	load();
}

DaycareData::DaycareData(DaycareData const& other) : GC::DaycareData(other) {}


DaycareData::~DaycareData(void) {
}

void DaycareData::loadFields(void) {
	GC::DaycareData::loadFields();
	pkm = new Pokemon(data + 8);
}

DaycareData* DaycareData::clone(void) const {
	return new DaycareData(*this);
}

DaycareData* DaycareData::create(void) const {
	return new DaycareData;
}

}
}