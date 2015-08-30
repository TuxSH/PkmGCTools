#ifndef _LIBPKMGC_COLO_POKEMON_H
#define _LIBPKMGC_COLO_POKEMON_H

#include <LibPkmGC/GC/Common/Pokemon.h>

namespace LibPkmGC {
namespace Colosseum {

/*
pkm
	0x00: u16 index
	0x02 : u16 ? ? ? ? (0 on shadow pkm)
	0x04 : u32 PID
	0x08 : VersionInfo version(4 bytes)
	0x0c : u16 locationCaught
	0x0e : u8 levelMet
	0x0f : u8 ballCaughtWith
	0x10 : u8 OTGender
	0x11 -- 0x13 : ? ? ? ? ?
	0x14 : u16 SID
	0x16 : u16 TID
	0x18 : OT Name(10 + 1 chars, limited to 8 in game)
	0x2e : Pkm Name(10 + 1, or 5 in game for jap.versions)
	0x44 : Pkm name backup
	0x5a -- 0x5b : u16 = field 0x02 backup
	0x5c : u32 experience
	0x60 : u8 currentLevel
	0x61 --  0x64 : ? ?
	0x65 : u16 status (u8 on XD)
	0x65 -- 0x67 : ? ?
	0x68 : u32 ? ?
	0x6c--0x78 ? ?
	0x78 : moves info
	0x88 : u16 itemHeld
	0x8a : u16 currentHP
	0x8c : u16 stats[6]
	0x98 : u16 EVs[6]
	0xa4 : u16 IVs[6]
	0xb0 : u16 happinness
	0xb2 : u8 contestsStats[5]
	0xb7 : u8 contestsRibbons[5]
	0xbc : u8 contestLuster
	0xbd : u8 specialRibbons[12]
	0xc9 : u8 unused ?
	0xca : u8 pkrsStatus
	0xcb : u8 ?
	0xcc : u8 abilityUsed
	0xcd : u16 ? ?
	0xcf : u8 marks
	// shadow pkm data ?
	0xd0--0xd7 : ? ?
	0xd8 : u16 shadowPkmID
	0xda--0xdb : padding ?
	0xdc : s32 purificationCounter
	0xe0 : u32 expStored
	0xe4 : u16 ? ?
	0xe6 : u16 ? ?
	0xfb : u8 encounterType
	0xfc--0x138 : ? ? ? ? ? ? ? ? ? ?
*/
class LIBPKMGC_DECL Pokemon : public GC::Pokemon {
public:
	static const size_t size = 0x138;
	Pokemon(void);
	Pokemon(const u8* inData);
	Pokemon(Pokemon const& other);
	~Pokemon(void);
	Pokemon* clone(void) const;
	Pokemon* create(void) const;

	void save(void);

	void swap(Pokemon& other);
	Pokemon& operator=(Pokemon const& other);

	bool hasSpecialAbility(void) const;
	void setSpecialAbilityStatus(bool status);
	bool specialAbilityStatus;

	Pokemon(XD::Pokemon const& other);
	Pokemon& operator=(GC::Pokemon const& other);
	void swap(GC::Pokemon & other);
protected:
	void loadFields(void);

};


}
}

#endif