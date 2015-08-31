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

#include <LibPkmGC/XD/Common/PlayerData.h>

namespace LibPkmGC {
namespace XD {

PlayerData::PlayerData(void) : GC::PlayerData(0x978) {
	initWithEmptyData();
}

PlayerData::PlayerData(const u8* inData) : GC::PlayerData(0x978, inData) {
	load();
}

PlayerData::PlayerData(PlayerData const& other) : GC::PlayerData(other) {}


PlayerData::~PlayerData(void){
}

PlayerData* PlayerData::clone(void) const {
	return new PlayerData(*this);
}

PlayerData* PlayerData::create(void) const {
	return new PlayerData;
}

void PlayerData::loadFields(void) {
	GC::PlayerData::loadFields();
	LD_FIELD_E(u8, trainerGender, 0x8e0, Gender);
	if (trainerGender > Female) trainerGender = Male;

	LD_FIELD(u32, money, 0x8e4);
	LD_FIELD(u32, pkCoupons, 0x8e8);

	LD_SUBSTRUCTURE_ARRAY(Pokemon, party, 6, 0x30);
	LD_SUBSTRUCTURE(BagData, bag, 0x4c8);
}

void PlayerData::save(void) {
	GC::PlayerData::save();
	if (trainerGender > Female) trainerGender = Male;
	SV_FIELD_E(u8, trainerGender, 0x8e0, Gender);

	SV_FIELD(u32, money, 0x8e4);
	SV_FIELD(u32, pkCoupons, 0x8e8);
	SV_FIELD(u32, pkCoupons, 0x8ec);

	SV_SUBSTRUCTURE_ARRAY(Pokemon, party, 6, 0x30);
	SV_SUBSTRUCTURE(BagData, bag, 0x4c8);

}

}
}