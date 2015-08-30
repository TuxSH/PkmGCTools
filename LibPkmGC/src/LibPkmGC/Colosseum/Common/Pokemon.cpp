#include <LibPkmGC/Colosseum/Common/Pokemon.h>

namespace LibPkmGC {
namespace Colosseum {

Pokemon::Pokemon(const u8* inData) : GC::Pokemon(0x138, inData) {
	load();
}

Pokemon::Pokemon(void) : GC::Pokemon(0x138) { initWithEmptyData(); }

Pokemon::~Pokemon(void) {
}

Pokemon::Pokemon(Pokemon const& other) : GC::Pokemon(other), specialAbilityStatus(other.specialAbilityStatus){}

Pokemon* Pokemon::clone(void) const { return new Pokemon(*this); }
Pokemon* Pokemon::create(void) const { return new Pokemon; }

void Pokemon::swap(Pokemon& other) {
	GC::Pokemon::swap(other);
	SW(specialAbilityStatus);
}

void Pokemon::loadFields(void) {
	u8 marksTmp = 0;
	
	LD_FIELD_E(u16, species, 0x00, PokemonSpeciesIndex);
	LD_FIELD(u32, PID, 0x04);
	version.load(data + 0x08);
	
	u16 locationCaught_tmp;
	LD_FIELD(u16, locationCaught_tmp, 0x0c);
	locationCaught = (u8)((locationCaught_tmp > 255) ? 255 : locationCaught_tmp);

	LD_FIELD(u8, levelMet, 0x0e);
	LD_FIELD_E(u8, ballCaughtWith, 0x0f, ItemIndex);
	LD_FIELD_E(u8, OTGender, 0x10, Gender);
	LD_FIELD(u16, SID, 0x14);
	LD_FIELD(u16, TID, 0x16);
	OTName = new GC::PokemonString(data + 0x18, 10);
	name = new GC::PokemonString(data + 0x2e, 10);
	LD_FIELD(u32, experience, 0x5c);

	LD_FIELD(u8, partyData.level, 0x60);
	if (partyData.level > 100) partyData.level = 100;
	LD_FIELD_E(u16, partyData.status, 0x65, PokemonStatus);
	partyData.status = (partyData.status != NoStatus && partyData.status < Poisoned && partyData.status > Asleep) ? NoStatus : partyData.status;
	LD_FIELD_E(u16, heldItem, 0x88, ItemIndex);
	
	LD_FIELD(u16, partyData.currentHP, 0x8a);
	LD_ARRAY(u16, partyData.stats, 6, 0x8c);
	
	u16 EVs_tmp[6]; // EVs are internally stored as u16
	LD_ARRAY(u16, EVs_tmp, 6, 0x98);
	for (size_t i = 0; i < 6; ++i) EVs[i] = (u8)((EVs_tmp[i] > 255) ? 255 : EVs_tmp[i]);

	LD_ARRAY(u8, IVs, 6, 0xa4);
	for (size_t i = 0; i < 6; ++i) IVs[i] = (IVs[i] > 31) ? 31 : IVs[i];
	
	u16 happiness_tmp;
	LD_FIELD(u16, happiness_tmp, 0xb0);
	happiness = (happiness_tmp > 255) ? 255 : happiness_tmp;


	LD_ARRAY(u8, contestStats, 5, 0xb2);
	LD_ARRAY_E(u8, contestAchievements, 5, 0xb7, ContestAchievementLevel);
	LD_FIELD(u8, contestLuster, 0xbc);

	LD_ARRAY_B(u8, specialRibbons, 12, 0xbd);

	LD_FIELD(u8, pkrsStatus, 0xca);
	LD_FIELD_B(u8, specialAbilityStatus, 0xcc);
	
	LD_FIELD(u8, marksTmp, 0xcf);

	LD_FIELD(u16, shadowPkmID, 0xd8);


	markings.load(marksTmp);
	for (size_t i = 0; i < 4; ++i)
		moves[i].load(data + 0x78 + 4 * i);
}

void Pokemon::save(void) {
	SV_FIELD_E(u16, species, 0x00, PokemonSpeciesIndex);
	SV_FIELD(u32, PID, 0x04);
	version.save(data + 0x08);
	SV_FIELD(u16, (u16) locationCaught, 0x0c);
	SV_FIELD(u8, levelMet, 0x0e);
	SV_FIELD_E(u8, ballCaughtWith, 0x0f, ItemIndex);
	SV_FIELD_E(u8, OTGender, 0x10, Gender);
	SV_FIELD(u16, SID, 0x14);
	SV_FIELD(u16, TID, 0x16);
	OTName->save(data + 0x18, 10);
	name->save(data + 0x2e, 10);
	name->save(data + 0x44, 10);
	SV_FIELD(u32, experience, 0x5c);

	if (partyData.level > 100) partyData.level = 100;
	SV_FIELD(u8, partyData.level, 0x60);
	partyData.status = (partyData.status != NoStatus && partyData.status < Poisoned && partyData.status > Asleep) ? NoStatus : partyData.status;
	SV_FIELD_E(u16, partyData.status, 0x65, PokemonStatus);
	SV_FIELD_E(u16, heldItem, 0x88, ItemIndex);

	SV_FIELD(u16, partyData.currentHP, 0x8a);
	SV_ARRAY(u16, partyData.stats, 6, 0x8c);
	
	u16 EVs_tmp[6]; for (size_t i = 0; i < 6; ++i) EVs_tmp[i] = (u16)EVs[i];
	SV_ARRAY(u16, EVs_tmp, 6, 0x98);
	for (size_t i = 0; i < 6; ++i) IVs[i] = (IVs[i] > 31) ? 31 : IVs[i];
	SV_ARRAY(u8, IVs, 6, 0xa4);
	
	SV_FIELD(u16, (u16)happiness, 0xb0);
	SV_ARRAY(u8, contestStats, 5, 0xb2);
	SV_ARRAY_E(u8, contestAchievements, 5, 0xb7, ContestAchievementLevel);
	SV_FIELD(u8, contestLuster, 0xbc);

	SV_ARRAY_B(u8, specialRibbons, 12, 0xbd);

	SV_FIELD(u8, pkrsStatus, 0xca);
	SV_FIELD_B(u8, specialAbilityStatus, 0xcc);

	SV_FIELD(u8, markings.save(), 0xcf);

	SV_FIELD(u16, shadowPkmID, 0xd8);

	for (size_t i = 0; i < 4; ++i)
		moves[i].save(data + 0x78 + 4 * i);


}

Pokemon& Pokemon::operator=(Pokemon const& other) {
	if (this != &other) {
		GC::Pokemon::operator=(other);
		CP(specialAbilityStatus);
	}
	return *this;
}

LIBPKMGC_GC_GEN_COL_VTF(Pokemon)
bool Pokemon::hasSpecialAbility(void) const {
	return isSpecialAbilityDefined() && specialAbilityStatus;
}

void Pokemon::setSpecialAbilityStatus(bool status) {
	specialAbilityStatus = isSpecialAbilityDefined() && status;
}

}
}