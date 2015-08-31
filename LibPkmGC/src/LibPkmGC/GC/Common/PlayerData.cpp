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

#include <LibPkmGC/GC/Common/PlayerData.h>

namespace LibPkmGC {
namespace GC {

PlayerData::PlayerData(size_t inSize, const u8* inData) : Base::DataStruct(inSize, inData) {
}


void PlayerData::deleteFields(void) {
	for (size_t i = 0; i < 6; ++i) delete party[i];
	delete bag;
	delete trainerName;
}

PlayerData::~PlayerData(void) {
	PlayerData::deleteFields();
}

PlayerData::PlayerData(PlayerData const& other) : Base::DataStruct(other), SID(other.SID), TID(other.TID), money(other.money), pkCoupons(other.pkCoupons),
trainerGender(other.trainerGender){
	CL(trainerName);
	CL_ARRAY(party, 6);
	CL(bag);
}

PlayerData& PlayerData::operator=(PlayerData const& other) {
	if (size != other.size) throw std::invalid_argument("Cannot assign because *this and other are of different types");
	Base::DataStruct::operator=(other);
	if (this != &other) {
		PlayerData::deleteFields();
		CP(SID); CP(TID); CP(money); CP(pkCoupons);
		CL(trainerName);
		CL_ARRAY(party, 6);
		CL(bag);
		CP(trainerGender);
	}
	return *this;
}

void PlayerData::swap(PlayerData& other) {
	if (size != other.size) throw std::invalid_argument("Cannot assign because *this and other are of different types");
	Base::DataStruct::swap(other);
	SW(SID); SW(TID); SW(money); SW(pkCoupons);
	CL(trainerName);
	SW_ARRAY(party, 6);
	SW(bag);
	SW(trainerGender);
}

void PlayerData::loadFields(void) {
	trainerName = new PokemonString(data, 10);
	LD_FIELD(u16, SID, 0x2c);
	LD_FIELD(u16, TID, 0x2e);
}

void PlayerData::save(void) {
	trainerName->save(data, 10);
	SV_FIELD(u16, SID, 0x2c);
	SV_FIELD(u16, TID, 0x2e);
}
void PlayerData::swapPokemon(size_t n, size_t m) {
	if ((n > 6) || (m > 6)) return;
	std::swap(party[n], party[m]);


}
}
}
