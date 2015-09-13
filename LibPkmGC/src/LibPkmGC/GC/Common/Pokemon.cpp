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
}


Pokemon::~Pokemon(void)
{
}

Pokemon::Pokemon(Pokemon const& other) : Base::Pokemon(other), shadowPkmID(other.shadowPkmID), encounterType(other.encounterType) {
	CL(OTName);
	CL(name);
	CP_ARRAY(pkmFlags, 3);
}

void Pokemon::swap(Pokemon& other) { 
	Base::Pokemon::swap(other);
	if (fixedSize == other.fixedSize) {
		SW(encounterType);
		SW(shadowPkmID);
	}
	else {
		other.encounterType = encounterType = 0;
		other.shadowPkmID = shadowPkmID = 0;
	}
	SW_ARRAY(pkmFlags, 3);
}

Pokemon& Pokemon::operator=(Pokemon const& other) {
	if (this != &other) {
		Base::Pokemon::operator=(other);
		if (other.fixedSize == fixedSize) {
			CP(encounterType);
			CP(shadowPkmID);
		}
		else {
			encounterType = 0;
			shadowPkmID = 0;
		}
		CP_ARRAY(pkmFlags, 3);
	}
	return *this;
}

bool Pokemon::hasSecondAbility(void) const {
	return pkmFlags[LIBPKMGC_GC_SECOND_ABILITY_FLAG];
}

void Pokemon::setSecondAbilityFlag(bool status) {
	pkmFlags[LIBPKMGC_GC_SECOND_ABILITY_FLAG] = status;
}

bool Pokemon::isEgg(void) const {
	return pkmFlags[LIBPKMGC_GC_EGG_FLAG];
}

void Pokemon::setEggFlag(bool status) {
	pkmFlags[LIBPKMGC_GC_EGG_FLAG] = status;
}

bool Pokemon::isMarkedAsInvalid(void) const {
	return pkmFlags[LIBPKMGC_GC_INVALID_POKEMON_FLAG];
}

void Pokemon::setInvalidPokemonFlag(bool status) {
	pkmFlags[LIBPKMGC_GC_INVALID_POKEMON_FLAG] = status;
}

}
}