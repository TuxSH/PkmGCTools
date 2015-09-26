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

#include <LibPkmGC/XD/Common/TrainerData.h>


namespace LibPkmGC {
namespace XD {

TrainerData::TrainerData(void) : GC::TrainerData(0x4c8) {
	initWithEmptyData();
}

TrainerData::TrainerData(const u8* inData) : GC::TrainerData(0x4c8, inData) {
	load();
}

TrainerData::TrainerData(TrainerData const& other) : GC::TrainerData(other) {}


TrainerData::~TrainerData(void) {
}

void TrainerData::loadFields(void) {
	GC::TrainerData::loadFields();
	LD_SUBSTRUCTURE_ARRAY(Pokemon, party, 6, 0x30);
}

TrainerData* TrainerData::clone(void) const {
	return new TrainerData(*this);
}

TrainerData* TrainerData::create(void) const {
	return new TrainerData;
}

}
}