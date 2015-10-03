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

#include <LibPkmGC/Colosseum/Common/Pokemon.h>

namespace LibPkmGC {
namespace Colosseum {

Pokemon::Pokemon(const u8* inData) : GC::Pokemon(0x138, inData) {
	load();
}

Pokemon::Pokemon(void) : GC::Pokemon(0x138) { initWithEmptyData(); }

Pokemon::~Pokemon(void) {
}

Pokemon::Pokemon(Pokemon const& other) : GC::Pokemon(other){}

Pokemon* Pokemon::clone(void) const { 
	return new Pokemon(*this); 
}
Pokemon* Pokemon::create(void) const { 
	return new Pokemon; 
}

void Pokemon::swap(Pokemon& other) {
	GC::Pokemon::swap(other);
}

void Pokemon::loadFields(void) {
	u8 marksTmp = 0;
	
	LD_FIELD_E(u16, species, 0x00, PokemonSpeciesIndex);
	LD_FIELD(u32, PID, 0x04);
	version.load(data + 0x08);
	
	LD_FIELD_CONV(u16, locationCaught, 0x0c, u8);

	LD_FIELD_MAX(u8, levelMet, 0x0e, 100);
	LD_FIELD_E_MAX(u8, ballCaughtWith, 0x0f, ItemIndex, PremierBall);
	if (ballCaughtWith == NoItem) ballCaughtWith = PokeBall;
	LD_FIELD_E_MAX(u8, OTGender, 0x10, Gender, Female);
	LD_FIELD(u16, SID, 0x14);
	LD_FIELD(u16, TID, 0x16);
	OTName = new GC::PokemonString(data + 0x18, 10);
	name = new GC::PokemonString(data + 0x2e, 10);
	LD_FIELD_MAX(u32, experience, 0x5c, getSpeciesExpTable(species)[100]);

	LD_FIELD(u8, partyData.level, 0x60);
	if (partyData.level > 100) partyData.level = 100;

	LD_FIELD_E(u16, partyData.status, 0x65, PokemonStatus);
	LD_FIELD(s8, partyData.turnsOfSleepRemaining, 0x69);
	LD_FIELD(s8, partyData.turnsOfBadPoison, 0x6b);

	u32 st = pokemonStatusToBitField(partyData.status, 0, partyData.turnsOfSleepRemaining);
	SV_FIELD(u32, st, 0x74);

	LD_FIELD_E(u16, heldItem, 0x88, ItemIndex);

	LD_ARRAY(u16, partyData.stats, 6, 0x8c);
	LD_FIELD_MAX(u16, partyData.currentHP, 0x8a, partyData.stats[0]);
	
	u16 EVs_tmp[6]; // EVs are internally stored as u16
	LD_ARRAY(u16, EVs_tmp, 6, 0x98);
	for (size_t i = 0; i < 6; ++i) EVs[i] = (u8)((EVs_tmp[i] > 255) ? 255 : EVs_tmp[i]);

	u16 IVs_tmp[6]; // IVs are internally stored as u16
	LD_ARRAY(u16, IVs_tmp, 6, 0xa4);
	for (size_t i = 0; i < 6; ++i) IVs[i] = (u8)((IVs_tmp[i] > 31) ? 31 : IVs_tmp[i]);
	
	LD_FIELD_CONV(u16, friendship, 0xb0, u8);

	LD_ARRAY(u8, contestStats, 5, 0xb2);
	LD_ARRAY_E_MAX(u8, contestAchievements, 5, 0xb7, ContestAchievementLevel, MasterContestWon);
	LD_FIELD(u8, contestLuster, 0xbc);

	LD_ARRAY_B(u8, specialRibbons, 12, 0xbd);
	LD_FIELD_MAX(u8, unimplementedRibbons, 0xc9, 15);

	LD_FIELD(u8, pokerusStatus, 0xca);
	LD_ARRAY_B(u8, pkmFlags, 3, 0xcb);
	LD_FIELD(u8, GCUnk, 0xce);
	LD_FIELD(u8, marksTmp, 0xcf);
	LD_FIELD_MAX(s8, partyData.pokerusDaysRemaining, 0xd0, 4);
	LD_FIELD(u16, unk2, 0xd2);
	LD_FIELD(u16, unk1, 0xd4);
	LD_FIELD(u16, shadowPkmID, 0xd8);

	LD_FIELD_B(u8, obedient, 0xf8);
	LD_FIELD(u8, encounterType, 0xfb);
	markings.load(marksTmp);
	for (size_t i = 0; i < 4; ++i)
		moves[i].load(data + 0x78 + 4 * i);
	pkmFlags[LIBPKMGC_GC_SECOND_ABILITY_FLAG] = isSecondAbilityDefined() && pkmFlags[LIBPKMGC_GC_SECOND_ABILITY_FLAG];

	normalizepokerus();
	normalizeStatus();
}

void Pokemon::save(void) {
	normalizepokerus();
	normalizeStatus();

	pkmFlags[LIBPKMGC_GC_SECOND_ABILITY_FLAG] = isSecondAbilityDefined() && pkmFlags[LIBPKMGC_GC_SECOND_ABILITY_FLAG];

	SV_FIELD_E(u16, species, 0x00, PokemonSpeciesIndex);
	SV_FIELD(u32, PID, 0x04);
	version.save(data + 0x08);
	SV_FIELD_CONV(u16, locationCaught, 0x0c, u8);
	SV_FIELD_MAX(u8, levelMet, 0x0e, 100);
	if (ballCaughtWith == NoItem || ballCaughtWith > PremierBall) ballCaughtWith = PokeBall;
	SV_FIELD_E_MAX(u8, ballCaughtWith, 0x0f, ItemIndex, PremierBall);
	SV_FIELD_E_MAX(u8, OTGender, 0x10, Gender, Female);
	SV_FIELD(u16, SID, 0x14);
	SV_FIELD(u16, TID, 0x16);
	OTName->save(data + 0x18, 10);
	name->save(data + 0x2e, 10);
	name->save(data + 0x44, 10);
	SV_FIELD_MAX(u32, experience, 0x5c, getSpeciesExpTable(species)[100]);

	if (partyData.level > 100) partyData.level = 100;
	SV_FIELD(u8, partyData.level, 0x60);
	SV_FIELD_E(u16, partyData.status, 0x65, PokemonStatus);
	SV_FIELD(s8, partyData.turnsOfSleepRemaining, 0x69);
	SV_FIELD(s8, partyData.turnsOfBadPoison, 0x6b);
	SV_FIELD_E(u16, heldItem, 0x88, ItemIndex);

	SV_FIELD_MAX(u16, partyData.currentHP, 0x8a, partyData.stats[0]);
	SV_ARRAY(u16, partyData.stats, 6, 0x8c);
	
	u16 EVs_tmp[6]; for (size_t i = 0; i < 6; ++i) EVs_tmp[i] = (u16)EVs[i];
	SV_ARRAY(u16, EVs_tmp, 6, 0x98);
	u16 IVs_tmp[6];
	for (size_t i = 0; i < 6; ++i) {
		IVs[i] = (IVs[i] > 31) ? 31 : IVs[i];
		IVs_tmp[i] = IVs[i];
	}
	SV_ARRAY(u16, IVs_tmp, 6, 0xa4);
	
	SV_FIELD(u16, (u16)friendship, 0xb0);
	SV_ARRAY(u8, contestStats, 5, 0xb2);
	SV_ARRAY_E(u8, contestAchievements, 5, 0xb7, ContestAchievementLevel);
	SV_FIELD(u8, contestLuster, 0xbc);

	SV_ARRAY_B(u8, specialRibbons, 12, 0xbd);
	SV_FIELD_MAX(u8, unimplementedRibbons, 0xc9, 15);


	SV_FIELD(u8, pokerusStatus, 0xca);
	SV_ARRAY_B(u8, pkmFlags, 3, 0xcb);
	SV_FIELD_MAX(u8, GCUnk, 0xce, 31);
	SV_FIELD(u8, markings.save(), 0xcf);
	SV_FIELD_MAX(s8, partyData.pokerusDaysRemaining, 0xd0, 4);
	SV_FIELD(u16, unk2, 0xd2);
	SV_FIELD(u16, unk1, 0xd4);
	SV_FIELD(u16, shadowPkmID, 0xd8);

	SV_FIELD_B(u8, obedient, 0xf8);
	SV_FIELD(u8, encounterType, 0xfb);
	for (size_t i = 0; i < 4; ++i)
		moves[i].save(data + 0x78 + 4 * i);


}

Pokemon& Pokemon::operator=(Pokemon const& other) {
	if (this != &other) {
		GC::Pokemon::operator=(other);
	}
	return *this;
}

LIBPKMGC_GC_GEN_COL_VTF(Pokemon)


}
}