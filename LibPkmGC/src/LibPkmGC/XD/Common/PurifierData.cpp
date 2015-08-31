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

#include <LibPkmGC/XD/Common/PurifierData.h>

namespace LibPkmGC {
namespace XD {

PurifierData::PurifierData(void) : Base::DataStruct(0x2298) {
	initWithEmptyData();
}

PurifierData::PurifierData(const u8* inData) : Base::DataStruct(0x2298, inData) {
	load();
}


void PurifierData::deleteFields(void) {
	for (size_t i = 0; i < 9; ++i) delete chambers[i];
}

PurifierData::~PurifierData(void) {
	PurifierData::deleteFields();
}

PurifierData::PurifierData(PurifierData const & other) : Base::DataStruct(other) {
	CL_ARRAY(chambers, 9);
}

PurifierData & PurifierData::operator=(PurifierData const & other){
	Base::DataStruct::operator=(other);
	if (this != &other) {
		CL_ARRAY(chambers, 9);
	}
	return *this;
}

void PurifierData::swap(PurifierData & other) {
	Base::DataStruct::swap(other);
	SW_ARRAY(chambers, 9);
}

PurifierData* PurifierData::clone(void) const {
	return new PurifierData(*this);
}

PurifierData* PurifierData::create(void) const {
	return new PurifierData;
}

void PurifierData::loadFields(void) {
	LD_SUBSTRUCTURE_ARRAY(PurificationChamber, chambers, 9, 0);
}

void PurifierData::save(void) {
	SV_SUBSTRUCTURE_ARRAY(PurificationChamber, chambers, 9, 0);
}

}
}