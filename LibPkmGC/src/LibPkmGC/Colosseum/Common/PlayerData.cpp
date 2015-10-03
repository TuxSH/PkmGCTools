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

PlayerData::PlayerData(PlayerData const& other) : GC::PlayerData(other) {
	CL(ruisName);
}

PlayerData& PlayerData::operator=(PlayerData const& other) {
	if (this != &other) {
		GC::PlayerData::operator=(other);
		CL(ruisName);
	}
	return *this;
}

void PlayerData::swap(PlayerData & other) {
	GC::PlayerData::swap(other);
	SW(ruisName);
}

LIBPKMGC_GC_GEN_NON_CONVERTIBLE_COL_VTF(PlayerData)

void PlayerData::_deleteFields_extension(void) {
	delete ruisName;
}

void PlayerData::deleteFields(void) {
	GC::PlayerData::deleteFields();
	_deleteFields_extension();
}

PlayerData::~PlayerData(void){
	_deleteFields_extension();
}

PlayerData* PlayerData::clone(void) const {
	return new PlayerData(*this);
}

PlayerData* PlayerData::create(void) const {
	return new PlayerData;
}

void PlayerData::loadFields(void) {
	LD_SUBSTRUCTURE(TrainerData, trainer, 0);
	LD_FIELD_E(u8, trainerGender, 0xa80, Gender);
	if (trainerGender > Female) trainerGender = Male;

	LD_FIELD_MAX(u32, pokeDollars, 0xa84, 9999999);
	LD_FIELD_MAX(u32, pokeCoupons, 0xa88, 9999999);

	ruisName = new GC::PokemonString(data + 0xac2, 10);

	LD_SUBSTRUCTURE(BagData, bag, 0x780);
}

void PlayerData::save(void) {
	GC::PlayerData::save();
	if (trainerGender > Female) trainerGender = Male;
	SV_FIELD_E(u8, trainerGender, 0xa80, Gender);
	SV_FIELD_MAX(u32, pokeDollars, 0xa84, 9999999);
	SV_FIELD_MAX(u32, pokeCoupons, 0xa88, 9999999);
	SV_FIELD(u32, pokeCoupons, 0xa8c);
	ruisName->save(data + 0xac2, 10);

	SV_SUBSTRUCTURE(BagData, bag, 0x780);
}

}
}