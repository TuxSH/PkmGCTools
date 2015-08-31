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

#include <LibPkmGC/Colosseum/Common/PlayerData.h>

namespace LibPkmGC {
namespace Colosseum {

PlayerData::PlayerData(void) : GC::PlayerData(0xb18) {
	initWithEmptyData();
}

PlayerData::PlayerData(const u8* inData) : GC::PlayerData(0xb18, inData) {
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

	LD_FIELD_E(u8, trainerGender, 0xa80, Gender);
	if (trainerGender > Female) trainerGender = Male;

	LD_FIELD(u32, money, 0xa84);
	LD_FIELD(u32, pkCoupons, 0xa88);

	LD_SUBSTRUCTURE_ARRAY(Pokemon, party, 6, 0x30);
	LD_SUBSTRUCTURE(BagData, bag, 0x780);
}

void PlayerData::save(void) {
	GC::PlayerData::save();
	if (trainerGender > Female) trainerGender = Male;
	SV_FIELD_E(u8, trainerGender, 0xa80, Gender);
	SV_FIELD(u32, money, 0xa84);
	SV_FIELD(u32, pkCoupons, 0xa88);
	SV_FIELD(u32, pkCoupons, 0xa8c);

	SV_SUBSTRUCTURE_ARRAY(Pokemon, party, 6, 0x30);
	SV_SUBSTRUCTURE(BagData, bag, 0x780);
}

}
}