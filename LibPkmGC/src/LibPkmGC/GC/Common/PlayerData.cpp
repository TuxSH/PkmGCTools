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
	delete bag;
	delete trainer;
}

PlayerData::~PlayerData(void) {
	PlayerData::deleteFields();
}

PlayerData::PlayerData(PlayerData const& other) : Base::DataStruct(other), money(other.money), pkCoupons(other.pkCoupons),
trainerGender(other.trainerGender){
	CL(trainer);
	CL(bag);
}

PlayerData& PlayerData::operator=(PlayerData const& other) {
	if (size != other.size) throw std::invalid_argument("Cannot assign because *this and other are of different types");
	Base::DataStruct::operator=(other);
	if (this != &other) {
		PlayerData::deleteFields();
		CP(money); CP(pkCoupons);
		CL(trainer);
		CL(bag);
		CP(trainerGender);
	}
	return *this;
}

void PlayerData::swap(PlayerData& other) {
	if (size != other.size) throw std::invalid_argument("Cannot assign because *this and other are of different types");
	Base::DataStruct::swap(other);
	SW(money); SW(pkCoupons);
	CL(trainer);
	SW(bag);
	SW(trainerGender);
}

void PlayerData::save(void) {
	SV_SUBSTRUCTURE2(TrainerData, trainer, 0);
}

}
}
