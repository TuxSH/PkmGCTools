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

#ifndef _LIBPKMGC_BASE_POKEMON_H
#define _LIBPKMGC_BASE_POKEMON_H

#include <LibPkmGC/Core/PokemonInfo.h>
#include <LibPkmGC/Core/ItemInfo.h>
#include <LibPkmGC/Core/VersionInfo.h>
#include <LibPkmGC/Core/TypeInfo.h>
#include <LibPkmGC/Base/DataStruct.h>
#include <LibPkmGC/Base/PokemonString.h>


#include <utility>

namespace LibPkmGC {

LIBPKMGC_FWD_DECL_GC_CLS(Pokemon)
namespace GC { class Pokemon;  }
namespace GBA { class Pokemon;  }

namespace Base {

class LIBPKMGC_DECL Pokemon : public DataStruct {
public:
	Pokemon(size_t inSize, const u8* inData = NULL);

	virtual ~Pokemon(void);

	virtual void swap(Pokemon& other);

	virtual Pokemon& operator=(Pokemon const& other);
	virtual Pokemon* clone(void) const = 0;
	virtual Pokemon* create(void) const = 0;

	void updateNamesLanguage(void);

	static u16 calculateStat(size_t statIndex, PokemonSpeciesIndex species, PokemonNatureIndex natureIndex, u8 level, u8 IV, u8 EV);
	static void calculateStats(PokemonSpeciesIndex species, PokemonNatureIndex natureIndex, u8 level, const u8 IVs[6], const u8 EVs[6], u16 outStats[6]);
	static u8 calculateLevelFromExp(PokemonSpeciesIndex species, u32 experience);
	static u32 calculateExpFromLevel(PokemonSpeciesIndex species, u8 level);

	static u32 fixExperienceProportionally(PokemonSpeciesIndex oldSpecies, u32 oldExp, PokemonSpeciesIndex newSpecies);

	u32 fixExperienceProportionally(PokemonSpeciesIndex newSpecies);
	PokemonSpeciesData getThisSpeciesData(void) const;
	const u32* getExpTable(void) const;
	void calculateStats(u16 outStats[6]) const;
	u8 calculateLevelFromExp(void) const;
	u32 calculateExpFromLevel(u8 lvl) const;

	void updateStats(void);
	void updateLevelFromExp(void);
	void updateExpFromLevel(u8 lvl);

	static bool isShiny(u32 PID, u16 TID, u16 SID);
	static PokemonNatureIndex getNature(u32 PID);
	static Gender getGender(PokemonSpeciesIndex species, u32 PID);
	static PokemonSpeciesIndex getWurmpleEvolution(u32 PID);
	static char getUnownForm(u32 PID);
	static std::pair<TypeIndex, u8> getHiddenPowerTypeAndPower(const u8 IVs[6]);

	bool isShiny(void) const;
	PokemonNatureIndex getNature(void) const;
	Gender getGender(void) const;

	PokemonSpeciesIndex getWurmpleEvolution(void) const;
	char getUnownForm(void) const;
	std::pair<TypeIndex, u8> getHiddenPowerTypeAndPower(void) const;


	bool isSecondAbilityDefined(void) const;
	PokemonAbilityIndex getAbility(void) const;
	virtual bool isEmptyOrInvalid(void) const;

	PokemonSpeciesIndex species; //u16
	ItemIndex heldItem;


	u8 friendship;
	u8 locationCaught; // u16 on Colo/XD
	ItemIndex ballCaughtWith;
	u8  levelMet;
	Gender  OTGender;
	PokemonString* OTName;
	PokemonString* name;
	u8  contestLuster;
	u8  pokerusStatus;
	PokemonMarkings  markings;

	u32 experience;
	u16 SID;
	u16 TID;
	u32 PID;

	u8 GCUnk;

	VersionInfo version;

	bool obedient;
	bool specialRibbons[12];
	u8 unimplementedRibbons;
	//u32 statusFlags;


	PokemonMove moves[4];
	u8 EVs[6];
	u8 IVs[6];

	u8 contestStats[5];
	ContestAchievementLevel contestAchievements[5];

	u16 unk1;
	u16 unk2;

	virtual bool isEgg(void) const = 0;
	virtual bool hasSecondAbility(void) const = 0;
	virtual void setEggFlag(bool flag) = 0;
	virtual void setSecondAbilityFlag(bool flag) = 0;
	virtual bool isMarkedAsInvalid(void) const = 0;
	virtual void setInvalidPokemonFlag(bool flag) = 0;

	struct PokemonComputedPartyData {
		s8 pokerusDaysRemaining;
		u16 currentHP;
		u8  level;
		PokemonStatus status;
		s8 turnsOfBadPoison, turnsOfSleepRemaining;
		u16 stats[6];
	};

	PokemonComputedPartyData partyData;

	void normalizepokerus(void);
	void normalizeStatus(void);

	void resetPartyData(void);
protected:
	Pokemon(Pokemon const& other);
	virtual void deleteFields(void);
private:
	void copyNonVirtual(Pokemon const& other);

};

}
}

#endif