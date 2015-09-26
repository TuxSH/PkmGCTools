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

#include <LibPkmGC/GC/Common/TrainerData.h>

namespace LibPkmGC {
namespace GC {

TrainerData::TrainerData(size_t inSize, const u8* inData) : Base::DataStruct(inSize, inData) {
}

void TrainerData::deleteFields(void) {
	for (size_t i = 0; i < 6; ++i) delete party[i];
	delete trainerName;
}

TrainerData::~TrainerData(void) {
	TrainerData::deleteFields();
}

TrainerData::TrainerData(TrainerData const& other) : Base::DataStruct(other) {
	CL_ARRAY(party, 6);
	CP(SID); CP(TID);
	CL(trainerName);
}

void TrainerData::swap(TrainerData& other) {
	Base::DataStruct::swap(other);
	SW(SID); SW(TID);
	SW(trainerName);
	for (size_t i = 0; i < 6; ++i) party[i]->swap(*(other.party[i]));
}

TrainerData& TrainerData::operator=(TrainerData const& other) {
	Base::DataStruct::operator=(other);
	if (this != &other) {
		CP(SID); CP(TID);
		CL(trainerName);
		for (size_t i = 0; i < 6; ++i) *party[i] = *(other.party[i]);
	}
	return *this;
}

void TrainerData::loadFields(void) {
	trainerName = new PokemonString(data, 10);
	LD_FIELD(u16, SID, 0x2c);
	LD_FIELD(u16, TID, 0x2e);
}

void TrainerData::save(void) {
	trainerName->save(data, 10);
	trainerName->save(data + 22, 10);
	SV_FIELD(u16, SID, 0x2c);
	SV_FIELD(u16, TID, 0x2e);
	SV_SUBSTRUCTURE_ARRAY2(Pokemon, party, 6, 0x30);
}

}
}