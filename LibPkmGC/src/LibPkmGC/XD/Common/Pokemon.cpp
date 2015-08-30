#include <LibPkmGC/XD/Common/Pokemon.h>

#define EGG_FLAG 0x80
#define SPECIAL_ABILITY_FLAG 0x40
#define INVALID_PKM_FLAG 0x20

namespace LibPkmGC {
namespace XD {

Pokemon::Pokemon(const u8* inData) : GC::Pokemon(0xc4, inData) {
	load();
}

Pokemon::Pokemon(void) : GC::Pokemon(0xc4) { initWithEmptyData(); }

Pokemon::~Pokemon(void) {
}

Pokemon::Pokemon(Pokemon const& other) : GC::Pokemon(other), pkmFlags(other.pkmFlags) {}
Pokemon* Pokemon::clone(void) const { return new Pokemon(*this); }
Pokemon* Pokemon::create(void) const { return new Pokemon; }

void Pokemon::swap(Pokemon& other) {
	GC::Pokemon::swap(other);
	SW(pkmFlags);
}

Pokemon& Pokemon::operator=(Pokemon const& other) {
	if (this != &other) {
		GC::Pokemon::operator=(other);
		CP(pkmFlags);
	}
	return *this;
}

void Pokemon::loadFields(void) {
	u8 marksTmp = 0;
	u16 specialRibbonsTmp = 0;
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
	LD_FIELD(u8, pkmFlags, 0x1d);
	LD_FIELD(u32, experience, 0x20);
	LD_FIELD(u16, SID, 0x24);
	LD_FIELD(u16, TID, 0x26);
	LD_FIELD(u32, PID, 0x28);

	OTName = new GC::PokemonString(data + 0x38, 10);
	name = new GC::PokemonString(data + 0x4e, 10);



	LD_FIELD(u16, specialRibbonsTmp, 0x7c);
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

	specialRibbonsTmp >>= 4;
	for (size_t i = 0; i < 12; ++i) {
		specialRibbons[11 - i] = (specialRibbonsTmp & 1) != 0;
		specialRibbonsTmp >>= 1;
	}
}

void Pokemon::save(void) {
	u16 specialRibbonsTmp = 0;

	for (size_t i = 0; i < 12; ++i) {
		specialRibbonsTmp <<= 1;
		specialRibbonsTmp |= (specialRibbons[i]) ? 1 : 0;
	}
	specialRibbonsTmp <<= 4;

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
	SV_FIELD(u8, pkmFlags, 0x1d);
	SV_FIELD(u32, experience, 0x20);
	SV_FIELD(u16, SID, 0x24);
	SV_FIELD(u16, TID, 0x26);
	SV_FIELD(u32, PID, 0x28);

	OTName->save(data + 0x38, 10);
	name->save(data + 0x4e, 10);
	name->save(data + 0x64, 10);

	SV_FIELD(u16, specialRibbonsTmp, 0x7c);
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

bool Pokemon::isEmptyOrInvalid(void) const {
	return GC::Pokemon::isEmptyOrInvalid() || (pkmFlags & INVALID_PKM_FLAG) != 0;
}
bool Pokemon::hasSpecialAbility(void) const{
	return isSpecialAbilityDefined() && ((pkmFlags & SPECIAL_ABILITY_FLAG) != 0);
}

void Pokemon::setSpecialAbilityStatus(bool status) {
	status = isSpecialAbilityDefined() && status;
	pkmFlags &= ~SPECIAL_ABILITY_FLAG; // reset bit 5
	pkmFlags |= (status) ? SPECIAL_ABILITY_FLAG : 0;
}

LIBPKMGC_GC_GEN_XD_VTF(Pokemon)
}
}