#include <LibPkmGC/GC/Common/Pokemon.h>


namespace LibPkmGC {
namespace GC {

Pokemon::Pokemon(size_t inSize, const u8* inData) : Base::Pokemon(inSize, inData) {
	usesPartyData = true;
}


Pokemon::~Pokemon(void)
{
}

Pokemon::Pokemon(Pokemon const& other) : Base::Pokemon(other), shadowPkmID(other.shadowPkmID) {}
void Pokemon::swap(Pokemon& other) { Base::Pokemon::swap(other); SW(shadowPkmID); }


PokemonAbilityIndex Pokemon::getAbility(void) const {
	const PokemonSpeciesData dt = getSpeciesData(species);
	return (hasSpecialAbility()) ? dt.possibleAbilities[1] : dt.possibleAbilities[0];
}

Pokemon& Pokemon::operator=(Pokemon const& other) {
	if (this != &other) {
		Base::Pokemon::operator=(other);
		CP(shadowPkmID);
	}
	return *this;
}

void Pokemon::swap(Base::Pokemon & other) {
	return swap((Pokemon&)other);
}
Pokemon& Pokemon::operator=(Base::Pokemon const& other) {
	return operator=((Pokemon const&)other);
}

}
}