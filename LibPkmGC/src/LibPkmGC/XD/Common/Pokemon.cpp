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
	LD_FIELD_E(u16, heldItem, 0x02, ItemIndex);
	LD_FIELD(u16, partyData.currentHP, 0x04);
	
	u16 happiness_tmp;
	LD_FIELD(u16, happiness_tmp, 0x06);
	happiness = (happiness_tmp > 255) ? 255 : happiness_tmp;

	u16 locationCaught_tmp;
	LD_FIELD(u16, locationCaught_tmp, 0x08);
	locationCaught = (u8)((locationCaught_tmp > 255) ? 255 : locationCaught_tmp);

	LD_FIELD(u8, levelMet, 0x0e);
	LD_FIELD_E(u8, ballCaughtWith, 0x0f, ItemIndex);
	LD_FIELD_E(u8, OTGender, 0x10, Gender);
	LD_FIELD(u8, partyData.level, 0x11);
	if (partyData.level > 100) partyData.level = 100;

	LD_FIELD(u8, contestLuster, 0x12);
	LD_FIELD(u8, pkrsStatus, 0x13);
	LD_FIELD(u8, marksTmp, 0x14);

	LD_FIELD_E(u8, partyData.status, 0x16, PokemonStatus);
	partyData.status = (partyData.status != NoStatus && partyData.status < Poisoned && partyData.status > Asleep) ? NoStatus : partyData.status;
	LD_BIT_ARRAY(u8, pkmFlags, 3, 0x1d);
	LD_BIT_ARRAY2(u8, XDPkmFlags, 3, 0x1d, 3);
	LD_FIELD(u32, experience, 0x20);
	LD_FIELD(u16, SID, 0x24);
	LD_FIELD(u16, TID, 0x26);
	LD_FIELD(u32, PID, 0x28);

	OTName = new GC::PokemonString(data + 0x38, 10);
	name = new GC::PokemonString(data + 0x4e, 10);

	LD_BIT_ARRAY(u16, specialRibbons, 12, 0x7c);
	LD_ARRAY(u16, partyData.stats, 6, 0x90);
	
	u16 EVs_tmp[6]; // EVs are internally stored as u16
	LD_ARRAY(u16, EVs_tmp, 6, 0x9c);
	for (size_t i = 0; i < 6; ++i) EVs[i] = (u8)((EVs_tmp[i] > 255) ? 255 : EVs_tmp[i]);
	
	LD_ARRAY(u8, IVs, 6, 0xa8);
	for (size_t i = 0; i < 6; ++i) IVs[i] = (IVs[i] > 31) ? 31 : IVs[i];

	LD_ARRAY(u8, contestStats, 6, 0xae);
	LD_ARRAY_E(u8, contestAchievements, 5, 0xb3, ContestAchievementLevel);

	LD_FIELD(u16, shadowPkmID, 0xba);

	markings.load(marksTmp);

	version.load(data + 0x34);
	for (size_t i = 0; i < 4; ++i)
		moves[i].load(data + 0x80 + 4 * i);

	pkmFlags[LIBPKMGC_GC_SECOND_ABILITY_FLAG] = isSecondAbilityDefined() && pkmFlags[LIBPKMGC_GC_SECOND_ABILITY_FLAG];
}

void Pokemon::save(void) {
	pkmFlags[LIBPKMGC_GC_SECOND_ABILITY_FLAG] = isSecondAbilityDefined() && pkmFlags[LIBPKMGC_GC_SECOND_ABILITY_FLAG];

	SV_FIELD_E(u16, species, 0x00, PokemonSpeciesIndex);
	SV_FIELD_E(u16, heldItem, 0x02, ItemIndex);
	SV_FIELD(u16, partyData.currentHP, 0x04);
	SV_FIELD(u16, (u16)happiness, 0x06);
	SV_FIELD(u16, (u16)locationCaught, 0x08);
	SV_FIELD(u8, levelMet, 0x0e);
	SV_FIELD_E(u8, ballCaughtWith, 0x0f, ItemIndex);
	SV_FIELD_E(u8, OTGender, 0x10, Gender);

	if (partyData.level > 100) partyData.level = 100;
	SV_FIELD(u8, partyData.level, 0x11);
	SV_FIELD(u8, contestLuster, 0x12);
	SV_FIELD(u8, pkrsStatus, 0x13);
	SV_FIELD(u8, markings.save(), 0x14);

	partyData.status = (partyData.status != NoStatus && partyData.status < Poisoned && partyData.status > Asleep) ? NoStatus : partyData.status;
	SV_FIELD_E(u8, partyData.status, 0x16, PokemonStatus);
	SV_BIT_ARRAY(u8, pkmFlags, 3, 0x1d);
	SV_BIT_ARRAY2(u8, XDPkmFlags, 3, 0x1d, 3);

	SV_FIELD(u32, experience, 0x20);
	SV_FIELD(u16, SID, 0x24);
	SV_FIELD(u16, TID, 0x26);
	SV_FIELD(u32, PID, 0x28);

	OTName->save(data + 0x38, 10);
	name->save(data + 0x4e, 10);
	name->save(data + 0x64, 10);

	SV_BIT_ARRAY(u16, specialRibbons, 12, 0x7c);
	SV_ARRAY(u16, partyData.stats, 6, 0x90);

	u16 EVs_tmp[6]; for (size_t i = 0; i < 6; ++i) EVs_tmp[i] = (u16)EVs[i];
	SV_ARRAY(u16, EVs_tmp, 6, 0x9c);
	for (size_t i = 0; i < 6; ++i) IVs[i] = (IVs[i] > 31) ? 31 : IVs[i];
	SV_ARRAY(u8, IVs, 6, 0xa8);
	
	
	SV_ARRAY(u8, contestStats, 6, 0xae);
	SV_ARRAY_E(u8, contestAchievements, 5, 0xb3, ContestAchievementLevel);

	SV_FIELD(u16, shadowPkmID, 0xba);

	version.save(data + 0x34);
	for (size_t i = 0; i < 4; ++i)
		moves[i].save(data + 0x80 + 4 * i);


}

LIBPKMGC_GC_GEN_XD_VTF(Pokemon)
}
}