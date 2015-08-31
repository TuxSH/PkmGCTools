#ifndef _LIBPKMGC_BASE_POKEMON_H
#define _LIBPKMGC_BASE_POKEMON_H

#include <LibPkmGC/Core/PokemonInfo.h>
#include <LibPkmGC/Core/ItemInfo.h>
#include <LibPkmGC/Base/DataStruct.h>
#include <LibPkmGC/Base/PokemonString.h>

namespace LibPkmGC {

LIBPKMGC_FWD_DECL_GC_CLS(Pokemon)


namespace Base {

class LIBPKMGC_DECL Pokemon : public DataStruct {
public:
	Pokemon(size_t inSize, const u8* inData = NULL);

	virtual ~Pokemon(void);

	virtual void swap(Pokemon& other);

	virtual Pokemon& operator=(Pokemon const& other);
	virtual Pokemon* clone(void) const = 0;
	virtual Pokemon* create(void) const = 0;

	static u16 calculateStat(size_t statIndex, PokemonSpeciesIndex species, PokemonNatureIndex natureIndex, u8 level, u8 IV, u8 EV);
	static void calculateStats(PokemonSpeciesIndex species, PokemonNatureIndex natureIndex, u8 level, const u8 IVs[6], const u8 EVs[6], u16 outStats[6]);
	static u8 calculateLevelFromExp(PokemonSpeciesIndex species, u32 experience);
	static u32 calculateExpFromLevel(PokemonSpeciesIndex species, u8 level);

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

	bool isShiny(void) const;
	PokemonNatureIndex getNature(void) const;
	Gender getGender(void) const;

	PokemonSpeciesIndex getWurmpleEvolution(void) const;
	char getUnownForm(void) const;

	bool isSecondAbilityDefined(void) const;
	virtual PokemonAbilityIndex getAbility(void) const = 0;
	virtual bool isEmptyOrInvalid(void) const;

	PokemonSpeciesIndex species; //u16
	ItemIndex heldItem;


	u8 happiness;
	u8 locationCaught; // u16 on Colo/XD
	ItemIndex ballCaughtWith;
	u8  levelMet;
	Gender  OTGender;
	PokemonString* OTName;
	PokemonString* name;
	u8  contestLuster;
	u8  pkrsStatus;
	PokemonMarkings  markings;

	u32 experience;
	u16 SID;
	u16 TID;
	u32 PID;

//	u8 encounterType;
	VersionInfo version;

	bool specialRibbons[12];
	//u32 statusFlags;


	PokemonMove moves[4];
	u8 EVs[6];
	u8 IVs[6];

	u8 contestStats[5];
	ContestAchievementLevel contestAchievements[5];

	bool usesPartyData; // we will avoid using ptrs here

	struct PokemonComputedPartyData {
		u16 currentHP;
		u8  level;
		PokemonStatus status;
		u16 stats[6];
	};

	PokemonComputedPartyData partyData;
	void resetPartyData(void);
protected:
	Pokemon(Pokemon const& other);
	virtual void deleteFields(void);
};

}
}

#endif