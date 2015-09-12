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

#include <LibPkmGC/XD/Common/Pokemon.h>

#define LIBPKMGC_XD_NOT_TRADABLE_IN_GAME_FLAG 0
#define LIBPKMGC_XD_UNKNOWN_FLAG 1
#define LIBPKMGC_XD_CAUGHT_FLAG 2

namespace LibPkmGC {
namespace XD {

Pokemon::Pokemon(const u8* inData) : GC::Pokemon(0xc4, inData) {
	load();
}

Pokemon::Pokemon(void) : GC::Pokemon(0xc4) { initWithEmptyData(); }

Pokemon::~Pokemon(void) {
}

Pokemon::Pokemon(Pokemon const& other) : GC::Pokemon(other) {
	CP_ARRAY(XDPkmFlags, 3);
}

Pokemon* Pokemon::clone(void) const { return new Pokemon(*this); }
Pokemon* Pokemon::create(void) const { return new Pokemon; }

void Pokemon::swap(Pokemon& other) {
	GC::Pokemon::swap(other);
	SW_ARRAY(XDPkmFlags, 3);
}

bool Pokemon::isEmptyOrInvalid(void) const {
	return (species >= Munchlax) || (species == NoSpecies) || !getSpeciesData(species).isValid || version.isIncomplete();
}

Pokemon& Pokemon::operator=(Pokemon const& other) {
	if (this != &other) {
		GC::Pokemon::operator=(other);
		CP_ARRAY(XDPkmFlags, 3);
	}
	return *this;
}

void Pokemon::loadFields(void) {
	u8 marksTmp = 0;
	LD_FIELD_E(u16, species, 0x00, PokemonSpeciesIndex);
	LD_FIELD_E(u8, heldItem, 0x03, ItemIndex);
	LD_FIELD(u16, partyData.currentHP, 0x04);
	
	LD_FIELD_CONV(u16, happiness, 0x06, u8);

	LD_FIELD_CONV(u16, locationCaught, 0x08, u8);
	
	LD_FIELD(u16, unk1, 0xa);
	LD_FIELD(u16, unk2, 0xc);
	LD_FIELD_MAX(u8, levelMet, 0x0e, 100);
	LD_FIELD_E_MAX(u8, ballCaughtWith, 0x0f, ItemIndex, PremierBall);
	if (ballCaughtWith == NoItem) ballCaughtWith = PokeBall;
	LD_FIELD_E_MAX(u8, OTGender, 0x10, Gender, Female);
	LD_FIELD(u8, partyData.level, 0x11);
	if (partyData.level > 100) partyData.level = 100;

	LD_FIELD(u8, contestLuster, 0x12);
	LD_FIELD(u8, pkrsStatus, 0x13);
	LD_FIELD(u8, marksTmp, 0x14);

	LD_FIELD_MAX(s8, partyData.pkrsDaysRemaining, 0x15, 4);
	LD_FIELD_E(u8, partyData.status, 0x16, PokemonStatus);
	LD_FIELD(s8, partyData.turnsOfBadPoison, 0x17);
	LD_FIELD(s8, partyData.turnsOfSleepRemaining, 0x18);
	LD_FIELD_MAX(u8, GCUnk, 0x1a, 31);
	LD_BIT_ARRAY(u8, pkmFlags, 3, 0x1d);
	LD_BIT_ARRAY2(u8, XDPkmFlags, 3, 0x1d, 3);
	LD_FIELD_MAX(u32, experience, 0x20, getSpeciesExpTable(species)[100]);
	LD_FIELD(u16, SID, 0x24);
	LD_FIELD(u16, TID, 0x26);
	LD_FIELD(u32, PID, 0x28);

	LD_FIELD_B(u8, obedient, 0x30);
	LD_FIELD(u8, encounterType, 0x33);
	OTName = new GC::PokemonString(data + 0x38, 10);
	name = new GC::PokemonString(data + 0x4e, 10);

	LD_BIT_ARRAY(u16, specialRibbons, 12, 0x7c);
	unimplementedRibbons = specialRibbons_tmp & 15; // specialRibbons_tmp is defined by LD_BIT_ARRAY
	LD_ARRAY(u16, partyData.stats, 6, 0x90);
	
	u16 EVs_tmp[6]; // EVs are internally stored as u16
	LD_ARRAY(u16, EVs_tmp, 6, 0x9c);
	for (size_t i = 0; i < 6; ++i) EVs[i] = (u8)((EVs_tmp[i] > 255) ? 255 : EVs_tmp[i]);
	
	LD_ARRAY(u8, IVs, 6, 0xa8);
	for (size_t i = 0; i < 6; ++i) IVs[i] = (IVs[i] > 31) ? 31 : IVs[i];

	LD_ARRAY(u8, contestStats, 5, 0xae);
	LD_ARRAY_E_MAX(u8, contestAchievements, 5, 0xb3, ContestAchievementLevel, MasterContestWon);

	LD_FIELD(u16, shadowPkmID, 0xba);

	markings.load(marksTmp);

	version.load(data + 0x34);
	for (size_t i = 0; i < 4; ++i)
		moves[i].load(data + 0x80 + 4 * i);

	if (partyData.currentHP > partyData.stats[0]) partyData.currentHP = partyData.stats[0];
	pkmFlags[LIBPKMGC_GC_SECOND_ABILITY_FLAG] = isSecondAbilityDefined() && pkmFlags[LIBPKMGC_GC_SECOND_ABILITY_FLAG];
	normalizePkrs();
	normalizeStatus();

}

void Pokemon::save(void) {
	normalizePkrs();
	normalizeStatus();

	pkmFlags[LIBPKMGC_GC_SECOND_ABILITY_FLAG] = isSecondAbilityDefined() && pkmFlags[LIBPKMGC_GC_SECOND_ABILITY_FLAG];
	if (partyData.currentHP > partyData.stats[0]) partyData.currentHP = partyData.stats[0];


	SV_FIELD_E(u16, species, 0x00, PokemonSpeciesIndex);
	SV_FIELD_E(u8, heldItem, 0x03, ItemIndex);
	SV_FIELD(u16, partyData.currentHP, 0x04);
	SV_FIELD_CONV(u16, happiness, 0x06, u8);
	SV_FIELD_CONV(u16, locationCaught, 0x08, u8);
	
	SV_FIELD(u16, unk1, 0xa);
	SV_FIELD(u16, unk2, 0xc);
	
	SV_FIELD_MAX(u8, levelMet, 0x0e, 100);
	if (ballCaughtWith == NoItem || ballCaughtWith > PremierBall) ballCaughtWith = PokeBall;
	SV_FIELD_E_MAX(u8, ballCaughtWith, 0x0f, ItemIndex, PremierBall);
	SV_FIELD_E_MAX(u8, OTGender, 0x10, Gender, Female);

	if (partyData.level > 100) partyData.level = 100;
	SV_FIELD(u8, partyData.level, 0x11);
	SV_FIELD(u8, contestLuster, 0x12);
	SV_FIELD(u8, pkrsStatus, 0x13);
	SV_FIELD(u8, markings.save(), 0x14);

	SV_FIELD_MAX(s8, partyData.pkrsDaysRemaining, 0x15, 4);
	SV_FIELD_E(u8, partyData.status, 0x16, PokemonStatus);
	SV_FIELD(s8, partyData.turnsOfBadPoison, 0x17);
	SV_FIELD(s8, partyData.turnsOfSleepRemaining, 0x18);
	SV_FIELD_MAX(u8, GCUnk, 0x1a, 31);
	SV_BIT_ARRAY(u8, pkmFlags, 3, 0x1d);
	SV_BIT_ARRAY2(u8, XDPkmFlags, 3, 0x1d, 3);

	SV_FIELD_MAX(u32, experience, 0x20, getSpeciesExpTable(species)[100]);
	SV_FIELD(u16, SID, 0x24);
	SV_FIELD(u16, TID, 0x26);
	SV_FIELD(u32, PID, 0x28);
	u32 st = pokemonStatusToBitField(partyData.status, 0, partyData.turnsOfSleepRemaining);
	SV_FIELD(u32, st, 0x2c);
	SV_FIELD_B(u8, obedient, 0x30);
	SV_FIELD(u8, encounterType, 0x33);
	OTName->save(data + 0x38, 10);
	name->save(data + 0x4e, 10);
	name->save(data + 0x64, 10);

	SV_BIT_ARRAY(u16, specialRibbons, 12, 0x7c);
	if (unimplementedRibbons > 15) unimplementedRibbons = 15;
	data[0x7d] = (data[0x7d] & 0xf0) | unimplementedRibbons;
	SV_ARRAY(u16, partyData.stats, 6, 0x90);

	u16 EVs_tmp[6]; for (size_t i = 0; i < 6; ++i) EVs_tmp[i] = (u16)EVs[i];
	SV_ARRAY(u16, EVs_tmp, 6, 0x9c);
	for (size_t i = 0; i < 6; ++i) IVs[i] = (IVs[i] > 31) ? 31 : IVs[i];
	SV_ARRAY(u8, IVs, 6, 0xa8);
	
	
	SV_ARRAY(u8, contestStats, 5, 0xae);
	SV_ARRAY_E_MAX(u8, contestAchievements, 5, 0xb3, ContestAchievementLevel, MasterContestWon);

	SV_FIELD(u16, shadowPkmID, 0xba);

	version.save(data + 0x34);
	for (size_t i = 0; i < 4; ++i)
		moves[i].save(data + 0x80 + 4 * i);


}

LIBPKMGC_GC_GEN_XD_VTF(Pokemon)
}
}