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

#include <LibPkmGC/GC/Common/DaycareData.h>

namespace LibPkmGC {
namespace GC {

DaycareData::DaycareData(size_t inSize, const u8* inData) : Base::DataStruct(inSize, inData) {
}

void DaycareData::deleteFields(void) {
	delete pkm;
}

DaycareData::~DaycareData(void) {
	DaycareData::deleteFields();
}

DaycareData::DaycareData(DaycareData const& other) : Base::DataStruct(other),
status(other.status), initialPkmLevel(other.initialPkmLevel), initialPkmPurifCounter(other.initialPkmPurifCounter) {
	pkm = other.pkm->clone();
}

void DaycareData::swap(DaycareData& other) {
	Base::DataStruct::swap(other);
	SW(status);
	SW(initialPkmLevel);
	SW(initialPkmPurifCounter);
	pkm->swap(*other.pkm);
}

DaycareData& DaycareData::operator=(DaycareData const& other) {
	Base::DataStruct::operator=(other);
	if (this != &other) {
		CP(status);
		CP(initialPkmLevel);
		CP(initialPkmPurifCounter);
		*pkm = *other.pkm;
	}
	return *this;
}

void DaycareData::loadFields(void) {
	LD_FIELD_E(s8, status, 0, DaycareStatus);
	status = ((status < NotVisited) || (status > PkmDeposited)) ? NoPkmDeposited : status;
	LD_FIELD(u8, initialPkmLevel, 1);
	LD_FIELD(u32, initialPkmPurifCounter, 4);
}

void DaycareData::save(void) {
	SV_FIELD_E(s8, status, 0, DaycareStatus);
	SV_FIELD(u8, initialPkmLevel, 1);
	SV_FIELD(u32, initialPkmPurifCounter, 4);

	SV_SUBSTRUCTURE2(Pokemon, pkm, 8);
}

}
}