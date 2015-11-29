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

#define TARGET_ENDIANNESS_LE
#include <LibPkmGC/GBA/Pokemon.h>

namespace LibPkmGC {
namespace GBA {

Pokemon::Pokemon(const u8* inData, u32 flags) : Base::Pokemon(100, inData) {
	_flags = flags;
	load(flags);
}

Pokemon* Pokemon::load80(const u8 * inData, u32 flags){
	u8 dta[100] = { 0 };
	std::copy(inData, inData + 80, dta);
	Pokemon* ret = new Pokemon(dta, flags);
	return ret;
}

Pokemon::Pokemon(void) : Base::Pokemon(100) {
	_flags = 1; // decrypted, unshuffled
	initWithEmptyData(1);
}

Pokemon::~Pokemon(void) {
}

Pokemon::Pokemon(Pokemon const& other) : Base::Pokemon(other) {
	CP(checksum);
	CP(GCFlags);
	CP(_flags);
	CP(_egg);
	CP(_secondAbility);
	CL(OTName);
	CL(name);
	setEggFlag(other.isEgg());
	setSecondAbilityFlag(other.hasSecondAbility());
	setInvalidPokemonFlag(other.isMarkedAsInvalid());
	updateNamesLanguage();
}
void Pokemon::swap(Pokemon& other) {
	Base::Pokemon::swap(other);
	SW(checksum);
	SW(GCFlags);
	SW(_flags);
	SW(_egg);
	SW(_secondAbility);

}

Pokemon* Pokemon::clone(void) const {
	return new Pokemon(*this);
}
Pokemon* Pokemon::create(void) const {
	return new Pokemon;
}

Pokemon& Pokemon::operator=(Pokemon const& other) {
	Base::Pokemon::operator=(other);
	if (this != &other) {
		CP(checksum);
		CP(GCFlags);
		CP(_flags);
		CP(_egg);
		CP(_secondAbility);
	}
	return *this;
}

bool Pokemon::hasSecondAbility(void) const {
	return _secondAbility;
}

void Pokemon::setSecondAbilityFlag(bool status) {
	_secondAbility = status;
}

bool Pokemon::isEgg(void) const {
	return _egg;
}

void Pokemon::setEggFlag(bool status) {
	_egg = status;
	GCFlags &= ~4;
	GCFlags |= ((_egg) ? 1 : 0) << 2;
}

bool Pokemon::isMarkedAsInvalid(void) const {
	return _invalid;
}

void Pokemon::setInvalidPokemonFlag(bool flag) {
	_invalid = flag;
	GCFlags &= ~1;
	GCFlags |= ((_invalid) ? 1 : 0);
}

bool Pokemon::isTradedFromGC(void) const {
	return _tradedFromGC;
}

void Pokemon::setTradedFromGCFlag(bool flag) {
	_tradedFromGC = flag;
	GCFlags &= ~2;
	GCFlags |= ((_tradedFromGC) ? 1 : 0) << 1;
}

void Pokemon::reload(const u8 * data, u32 inFlags) {
	if (data == NULL) return;
}

static const size_t shuffleTable[24][4] = {
	{ 0,1,2,3 },{ 0,1,3,2 },{ 0,2,1,3 },{ 0,2,3,1 },
	{ 0,3,1,2 },{ 0,3,2,1 },{ 1,0,2,3 },{ 1,0,3,2 },
	{ 1,2,0,3 },{ 1,2,3,0 },{ 1,3,0,2 },{ 1,3,2,0 },
	{ 2,0,1,3 },{ 2,0,3,1 },{ 2,1,0,3 },{ 2,1,3,0 },
	{ 2,3,0,1 },{ 2,3,1,0 },{ 3,0,1,2 },{ 3,0,2,1 },
	{ 3,1,0,2 },{ 3,1,2,0 },{ 3,2,0,1 },{ 3,2,1,0 }
};

inline void crypt_impl(u32 key, u8* data, u8* outData) {
	u32 D;

	for (size_t i = 0; i < 48; i += 4) {
		std::copy(data + 32 + i, data + 36 + i, (u8*)&D);
		D ^= key;
		std::copy((u8*)&D, 4 + (u8*)&D, outData + 32 + i);
	}
}
void Pokemon::decryptOrEncrypt(u8 * outData) {
	u32 key = PID ^ (((u32)SID << 16) | TID);

	u8 buf[48];

	const size_t *P = shuffleTable[PID % 24];

	if (outData == data) { // when unshuffling
		for (size_t i = 0; i < 4; ++i)
			std::copy(data + 32 + 12*i, data + 32 + 12*i + 12, buf + 12 * P[i]);
		std::copy(buf, buf + 48, outData + 32);

	}
	else { // shuffling
		for (size_t i = 0; i < 4; ++i)
			std::copy(data + 32 + 12 * P[i], data + 32 + 12 * P[i] + 12, buf + 12 * i);
		std::copy(buf, buf + 48, outData + 32);
	}
	crypt_impl(key, outData, outData);

}

void Pokemon::load(u32 flags) {
	if (flags == 0) {
		u8 buf[48];
		std::copy(data + 32, data + 80, buf);

		load(1); // assume it is unencrypted by default
		if (!checkChecksum(false)) {
			deleteFields();
			load(2);
			if (!checkChecksum(false)) {
				std::copy(buf, buf + 48, data + 32);
				load(1);
			}
		}
	}
	else {
		loadData(flags);
		loadFields();
	}
}

void Pokemon::loadData(u32 flags) {
	LD_FIELD(u32, PID, 0);
	LD_FIELD(u16, TID, 4);
	LD_FIELD(u16, SID, 6);

	if(flags == 2)
		decryptOrEncrypt(data);
	_flags = 1;
}

void Pokemon::loadFields(void) {
	u8 lg = data[18];
	markings.load(data[27]);

	LD_FIELD(u8, GCFlags, 19);
	_invalid = (GCFlags & 1) != 0;
	_tradedFromGC = (GCFlags & 2) != 0;
	GCUnk = GCFlags >> 3;

	LD_FIELD(u16, checksum, 28);
	LD_FIELD(u16, unk1, 30);
	LD_FIELD_E(u16, species, 32, PokemonSpeciesIndex);
	LD_FIELD_E(u16, heldItem, 34, ItemIndex);
	LD_FIELD_MAX(u32, experience, 36, getSpeciesExpTable(species)[100]);
	LD_FIELD(u8, friendship, 41);
	LD_FIELD(u16, unk2, 42);
	for (size_t i = 0; i < 6; ++i) EVs[GBAStatsOrder[i]] = data[56 + i];

	LD_ARRAY(u8, contestStats, 5, 62);
	LD_FIELD(u8, contestLuster, 67);

	LD_FIELD(u8, pokerusStatus, 68);
	LD_FIELD(u8, locationCaught, 69);

	u16 origins;
	LD_FIELD(u16, origins, 70);

	levelMet = (u8)(origins & 0x7f);
	if (levelMet > 100) levelMet = 100;
	origins >>= 7;
	u8 gm = (u8)(origins & 0xf);
	origins >>= 4;
	u16 pkb = origins & 0xf;
	ballCaughtWith = (pkb > 12 || pkb == 0) ? PokeBall : (ItemIndex) pkb;
	origins >>= 4;
	OTGender = (Gender)(origins & 1);

	u32 iea;
	LD_FIELD(u32, iea, 72);
	for (size_t i = 0; i < 6; ++i) {
		IVs[GBAStatsOrder[i]] = (u8)(iea & 0x1f);
		iea >>= 5;
	}
	_egg = (iea & 1) != 0;
	_secondAbility = (iea & 2) != 0;

	u32 ribbons;
	LD_FIELD(u32, ribbons, 76);

	for (size_t i = 0; i < 5; ++i) {
		contestAchievements[i] = (ContestAchievementLevel)(ribbons & 7);
		if (contestAchievements[i] > MasterContestWon) contestAchievements[i] = NoContestWon;
		ribbons >>= 3;
	}
	for (size_t i = 0; i < 12; ++i) {
		specialRibbons[i] = (ribbons & 1) != 0;
		ribbons >>= 1;
	}
	unimplementedRibbons = (u8)(ribbons & 15);
	ribbons >>= 4;
	obedient = ribbons != 0;

	u8 PPBonuses = data[40];
	PokemonMoveIndex mvs[4];
	LD_ARRAY_E_MAX(u16, mvs, 4, 44, PokemonMoveIndex, PsychoBoost);
	for (size_t i = 0; i < 4; ++i) {
		moves[i].move = mvs[i];
		moves[i].currentPPs = data[52 + i];
		moves[i].nbPPUpsUsed = (PPBonuses & 3);
		PPBonuses >>= 2;
	}

	u32 st;
	LD_FIELD(u32, st, 80);
	partyData.status = pokemonStatusFromBitField((u16)st, &(partyData.turnsOfBadPoison), &(partyData.turnsOfSleepRemaining));

	LD_FIELD_MAX(u8, partyData.level, 84, 100);
	LD_FIELD_MAX(s8, partyData.pokerusDaysRemaining, 85, 4);
	LD_FIELD(u16, partyData.currentHP, 86);
	u16 sta[6];
	LD_ARRAY(u16, sta, 6, 88);
	bool regen = true;
	for (size_t i = 0; i < 6; ++i) {
		partyData.stats[GBAStatsOrder[i]] = sta[i];
		if (sta[i] != 0) regen = false;
	}
	if (regen) resetPartyData();
	if (partyData.currentHP > partyData.stats[0]) partyData.currentHP = partyData.stats[0];

	version.load(lg, gm);

	name = new PokemonString(data + 8, 10, version.language == Japanese);
	OTName = new PokemonString(data + 20, 7, version.language == Japanese);

	normalizepokerus();
	normalizeStatus();

	if (!checkChecksum(false)) setInvalidPokemonFlag(true);

	updateNamesLanguage();

}




bool Pokemon::checkChecksum(bool fix) {
	u16 newChecksum = 0;
	for (size_t i = 0; i < 48; i += 2)
		newChecksum += toInteger<u16, u8*>(data + 32 + i);
	bool ret = newChecksum == checksum;
	if (fix) checksum = newChecksum;
	return ret;
}

bool Pokemon::isEmptyOrInvalid(void) const {
	return Base::Pokemon::isEmptyOrInvalid() || !const_cast<Pokemon*>(this)->checkChecksum(false) || (GCFlags & 2) == 0;
}

void Pokemon::save(void) {
	u8 lg, gm;
	data[27] = markings.save();
	version.save(lg, gm);

	normalizepokerus();
	updateNamesLanguage();

	name->save(data + 8, 10);
	OTName->save(data + 20, 7);

	data[18] = lg;

	SV_FIELD(u32, PID, 0);
	SV_FIELD(u16, TID, 4);
	SV_FIELD(u16, SID, 6);

	setTradedFromGCFlag(_tradedFromGC);
	setInvalidPokemonFlag(_invalid);
	setEggFlag(_egg);
	GCFlags &= 7;
	if (GCUnk > 31) GCUnk = 31;
	GCFlags |= GCUnk << 3;
	SV_FIELD(u8, GCFlags, 19);
	SV_FIELD(u16, unk1, 30);
	SV_FIELD_E(u16, species, 32, PokemonSpeciesIndex);
	SV_FIELD_E(u16, heldItem, 34, ItemIndex);
	SV_FIELD_MAX(u32, experience, 36, getSpeciesExpTable(species)[100]);
	SV_FIELD(u8, friendship, 41);
	SV_FIELD(u16, unk2, 42);

	for (size_t i = 0; i < 6; ++i) data[56 + i] = EVs[GBAStatsOrder[i]];
	SV_ARRAY(u8, contestStats, 5, 62);
	SV_FIELD(u8, contestLuster, 67);

	SV_FIELD(u8, pokerusStatus, 68);
	SV_FIELD(u8, locationCaught, 69);

	u16 origins = 0;
	if (levelMet > 100) levelMet = 100;
	origins |= levelMet;
	origins |= (u16) gm << 7;
	if (ballCaughtWith == 0 || ballCaughtWith > PremierBall) ballCaughtWith = PokeBall;
	origins |= (u16)ballCaughtWith << 11;
	if ((u32)OTGender > (u32)Female) OTGender = Male;
	origins |= (u16)OTGender << 15;
	SV_FIELD(u16, origins, 70);

	u32 iea = 0;
	for (size_t i = 0; i < 6; ++i) {
		if (IVs[GBAStatsOrder[i]] > 31) IVs[GBAStatsOrder[i]] = 31;
		iea |= IVs[GBAStatsOrder[i]] << (5 * i);
	}
	iea |= ((_egg) ? 1 : 0) << 30;
	iea |= ((_secondAbility) ? 1 : 0) << 31;
	SV_FIELD(u32, iea, 72);


	u32 ribbons = 0;

	for (size_t i = 0; i < 5; ++i) {
		if ((u32)contestAchievements[i] >(u32) MasterContestWon) contestAchievements[i] = NoContestWon;
		ribbons |= (u32)contestAchievements[i] << (3 * i);
	}
	for (size_t i = 0; i < 12; ++i) 
		ribbons |= ((specialRibbons[i]) ? 1 : 0) << (15 + i);
	unimplementedRibbons = (unimplementedRibbons > 15) ? 15 : unimplementedRibbons;
	ribbons |= (u32)unimplementedRibbons << 27;
	ribbons |= ((obedient) ? 1 : 0) << 31;
	SV_FIELD(u32, ribbons, 76);

	u8 PPBonuses = 0;
	for (size_t i = 0; i < 4; ++i) {
		if ((u32)moves[i].move >(u32)PsychoBoost) moves[i].move = NoMove;
		SV_FIELD(u16, (u16)moves[i].move, 44 + 2 * i);
		SV_FIELD(u8, moves[i].currentPPs, 52 + i);
		if (moves[i].nbPPUpsUsed > 3) moves[i].nbPPUpsUsed = 3;
		PPBonuses |= moves[i].nbPPUpsUsed << (2 * i);
	}
	SV_FIELD(u8, PPBonuses, 40);

	normalizeStatus();
	u32 st = pokemonStatusToBitField(partyData.status, partyData.turnsOfBadPoison, partyData.turnsOfSleepRemaining);
	SV_FIELD(u32, st, 80);

	SV_FIELD_MAX(u8, partyData.level, 84, 100);
	SV_FIELD_MAX(s8, partyData.pokerusDaysRemaining, 85, 4);
	if (partyData.pokerusDaysRemaining < -1) partyData.pokerusDaysRemaining = -1;
	SV_FIELD_MAX(u16, partyData.currentHP, 86, partyData.stats[0]);
	u16 sta[6];
	for (size_t i = 0; i < 6; ++i) sta[i] = partyData.stats[GBAStatsOrder[i]];
	SV_ARRAY(u16, sta, 6, 88);


	checkChecksum(true);
	SV_FIELD(u32, checksum, 28);

}

void Pokemon::saveEncrypted(u8 * outData) {
	save();
	std::copy(data, data + 32, outData);
	std::copy(data + 80, data + 100, outData + 80);
	if (outData == NULL || outData == data) return;
	decryptOrEncrypt(outData);
}


}
}

#undef TARGET_ENDIANNESS_LE
