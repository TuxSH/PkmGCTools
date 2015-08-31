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
	const PokemonSpeciesData dt = getThisSpeciesData();
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

void Pokemon::swap(Base::Pokemon & other) {
	return swap((Pokemon&)other);
}
Pokemon& Pokemon::operator=(Base::Pokemon const& other) {
	return operator=((Pokemon const&)other);
}

}
}