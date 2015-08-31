#ifndef _LIBPKMGC_XD_POKEMON_H
#define _LIBPKMGC_XD_POKEMON_H

#include <LibPkmGC/GC/Common/Pokemon.h>

namespace LibPkmGC {
namespace XD {

/*
	0x00: u16 species
	0x02: u16 itemHeld
	0x04: u16 currentHP
	0x06: u16 happiness
	0x08: u16 locationCaught
	// 0x09 -- 0xd :: ??
	0x0e: u8  levelMet
	0x0f: u8  ballCaughtWith
	0x10: u8  OTGender (00 male 01 female 02 genderless=none)
	0x11: u8  currentLevel
	0x12: u8  Contest Luster
	0x13: u8  pkrsStatus
	0x14: u8  marks (bitfield)
	0x15: 0xff ?
	0x16: u16 status (3 psn, 4 psn (toxic ?), 5 par, 6 brn, 7 frzn, 8 slp)
	0x17: ?
	0x18 -- 0x1b : ? (0x50)
	0x1d: u8 pkmFlags
		bit 7: egg flag
		bit 6: special (second) ability flag. Pokémon XD's catchable Pkms have a 50% chance to have their special ability
		bit 5: invalidity flag. MUST **NOT** BE SET for the Pokémon to be considered as valid ("not empty")
		bit 4: "not tradable in game" flag
		bit 3: ?
		bit 2: "caught" flag
	0x1e 0x1f : ??
	0x20: u32 experience
	0x24: u16 SID
	0x26: u16 TID
	0x28: u32 PID
	0x2c -- 0x32 : ?? (0 on shadow pkm)
	0x33: u8 encounterType
	0x34 -- 0x37 : Version info (actual region, original region, original language)
	0x38: GC::PokemonString OTName (10+1 chars = 22 bytes)
	0x4e: GC::PokemonString name (10+1 chars)
	0x64: pkm name backup
	0x7a -- 0x7b: ??
	0x7c: u16 specialRibbons
	0x7e -- 0x7f: ??
	0x80: moves[4]{u16 moveID, u8 basePP (?), u8 nbPPUps}
	0x90: u16 stats[6]
	0x9c: u16 EVs[6]
	0xa8: u8 IVs[6]
	0xae: u8 contestStats[6] (0 to 255)
	0xb3: u8 contestAchievements[5]
	0xb7: unused
	0xb8 : u16 ??
	0xba: shadow pkm id
	0xbc -- 0xbf : ??? ????
	0xc0 -- 0xc1 : unused ?
	0xc2: party identify (lead = 00, 01 otherwise)
*/

class LIBPKMGC_DECL Pokemon : public GC::Pokemon {
public:
	static const size_t size = 0xc4;
	Pokemon(void);
	Pokemon(const u8* inData);
	Pokemon(Pokemon const& other);
	~Pokemon(void);
	Pokemon* clone(void) const;
	Pokemon* create(void) const;

	void save(void);

	void swap(Pokemon& other);
	Pokemon& operator=(Pokemon const& other);

	Pokemon(Colosseum::Pokemon const& other);
	Pokemon& operator=(GC::Pokemon const& other);
	void swap(GC::Pokemon & other);

	bool XDPkmFlags[3];
private:
	void loadFields(void);

};

}
}

#endif