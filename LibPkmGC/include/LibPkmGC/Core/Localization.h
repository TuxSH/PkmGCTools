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

#ifndef _LIBPKMGC_LOCALIZATION_H
#define _LIBPKMGC_LOCALIZATION_H

#include <LibPkmGC/Core/PokemonInfo.h>
#include <LibPkmGC/Core/ItemInfo.h>
#include <LibPkmGC/Core/VersionInfo.h>
#include <LibPkmGC/Core/TypeInfo.h>

namespace LibPkmGC {
namespace Localization {

LIBPKMGC_DECL size_t itemIndexToNameIndex(ItemIndex index, bool isXD = false);
LIBPKMGC_DECL ItemIndex nameIndexToItemIndex(size_t index, bool isXD = false);

LIBPKMGC_DECL size_t pkmSpeciesIndexToNameIndex(PokemonSpeciesIndex index);
LIBPKMGC_DECL PokemonSpeciesIndex nameIndexToPkmSpeciesIndex(size_t index);

LIBPKMGC_DECL const char* getPokemonSpeciesName(LanguageIndex language, PokemonSpeciesIndex index);
LIBPKMGC_DECL const char*  getPokemonSpeciesNameByPkdxIndex(LanguageIndex language, u16 pkdexIndex);

LIBPKMGC_DECL const char*  getPokemonNatureName(LanguageIndex language, PokemonNatureIndex index);
LIBPKMGC_DECL const char*  getPokemonMoveName(LanguageIndex language, PokemonMoveIndex index);
LIBPKMGC_DECL const char*  getPokemonAbilityName(LanguageIndex language, PokemonAbilityIndex index);

LIBPKMGC_DECL const char* getItemName(LanguageIndex language, ItemIndex index, bool isXD = false);

LIBPKMGC_DECL const char* getRibbonDescription(LanguageIndex language, size_t index);
// Ribbons: Marine, Land, Sky, Country, National, Earth, World, Unused 1,2,3,4

LIBPKMGC_DECL const char* getTypeName(LanguageIndex language, TypeIndex index);
}
}

#endif