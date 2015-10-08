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

#ifndef _LIBPKMGC_SHADOW_POKEMON_INFO_H
#define _LIBPKMGC_SHADOW_POKEMON_INFO_H


#include <LibPkmGC/Core/PokemonInfo.h>

namespace LibPkmGC {

struct LIBPKMGC_DECL ShadowPokemonInfo {
	PokemonSpeciesIndex species;
	u8 encounterLevel;
	u16 basePurificationCounter;
};

LIBPKMGC_DECL ShadowPokemonInfo getShadowPokemonInfo(PokemonSpeciesIndex index, bool isXD = false);
LIBPKMGC_DECL ShadowPokemonInfo getShadowPokemonInfo(PokemonSpeciesIndex index, u8 levelMet = 0);


}

#endif