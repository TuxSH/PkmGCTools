#include <LibPkmGC/GC/Common/Pokemon.h>


namespace LibPkmGC {
namespace GC {

Pokemon::Pokemon(size_t inSize, const u8* inData) : Base::Pokemon(inSize, inData) {
	usesPartyData = true;
}


Pokemon::~Pokemon(void)
{
}

Pokemon::Pokemon(Pokemon const& other) : Base::Pokemon(other), shadowPkmID(other.shadowPkmID) {
	CP_ARRAY(pkmFlags, 3);
}
void Pokemon::swap(Pokemon& other) { 
	Base::Pokemon::swap(other); 
	SW(shadowPkmID); 
	SW_ARRAY(pkmFlags, 3);
}


PokemonAbilityIndex Pokemon::getAbility(void) const {
	const PokemonSpeciesData dt = getSpeciesData(species);
	return (pkmFlags[LIBPKMGC_GC_SECOND_ABILITY_FLAG]) ? dt.possibleAbilities[1] : dt.possibleAbilities[0];
}

Pokemon& Pokemon::operator=(Pokemon const& other) {
	if (this != &other) {
		Base::Pokemon::operator=(other);
		CP(shadowPkmID);
		CP_ARRAY(pkmFlags, 3);
	}
	return *this;
}

/*
bool Pokemon::hasSecondAbility(void) const {
	return isSecondAbilityDefined() && pkmFlags[LIBPKMGC_GC_SECOND_ABILITY_FLAG];
}

void Pokemon::setSpecialAbilityStatus(bool status) {
	pkmFlags[LIBPKMGC_GC_SECOND_ABILITY_FLAG] = status;
}*/

void Pokemon::swap(Base::Pokemon & other) {
	return swap((Pokemon&)other);
}
Pokemon& Pokemon::operator=(Base::Pokemon const& other) {
	return operator=((Pokemon const&)other);
}

}
}