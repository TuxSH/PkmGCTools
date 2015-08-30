#ifndef _LIBPKMGC_LOCALIZATION_H
#define _LIBPKMGC_LOCALIZATION_H

#include <LibPkmGC/Core/PokemonInfo.h>
#include <LibPkmGC/Core/ItemInfo.h>
#include <LibPkmGC/Core/Detail/SpeciesNames.h>
#include <LibPkmGC/Core/Detail/NatureNames.h>
#include <LibPkmGC/Core/Detail/MoveNames.h>
#include <LibPkmGC/Core/Detail/AbilityNames.h>
#include <LibPkmGC/Core/Detail/ItemNames.h>

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


}
}

#endif