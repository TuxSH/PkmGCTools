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

#include <LibPkmGC/Core/ShadowPokemonInfo.h>
#include <boost/unordered_map.hpp>

namespace {

using namespace LibPkmGC;

typedef boost::unordered_map<PokemonSpeciesIndex, ShadowPokemonInfo> table_t;

static table_t generateColosseumShadowPkmInfoTbl(void) {
	table_t tbl;

	static const ShadowPokemonInfo ar[] = {
		{ Makuhita, 30, 3000 },
		{ Bayleef, 30, 3000 },
		{ Quilava, 30, 3000 },
		{ Croconaw, 30, 3000 },
		{ Slugma, 30, 4000 },
		{ Noctowl, 30, 3000 },
		{ Flaaffy, 30, 3000 },
		{ Skiploom, 30, 3000 },
		{ Quagsire, 30, 4000 },
		{ Misdreavus, 30, 4000 },
		{ Furret, 33, 5000 },
		{ Yanma, 33, 5000 },
		{ Remoraid, 20, 4000 },
		{ Mantine, 33, 5000 },
		{ Qwilfish, 33, 5000 },
		{ Dunsparce, 33, 5000 },
		{ Meditite, 33, 5000 },
		{ Swablu, 33, 5000 },
		{ Sudowoodo, 35, 10000 },
		{ Hitmontop, 38, 6000 },
		{ Entei, 40, 13000 },
		{ Ledian, 40, 6000 },
		{ Suicune, 40, 13000 },
		{ Gligar, 43, 6000 },
		{ Sneasel, 43, 6000 },
		{ Piloswine, 43, 6000 },
		{ Stantler, 43, 6000 },
		{ Ariados, 43, 6000 },
		{ Aipom, 43, 6000 },
		{ Murkrow, 43, 6000 },
		{ Forretress, 43, 6000 },
		{ Granbull, 43, 6000 },
		{ Vibrava, 43, 6000 },
		{ Raikou, 40, 13000 },
		{ Sunflora, 45, 7000 },
		{ Delibird, 45, 7000 },
		{ Heracross, 45, 7000 },
		{ Skarmory, 47, 13000 },
		{ Miltank, 48, 7000 },
		{ Absol, 48, 7000 },
		{ Houndoom, 48, 7000 },
		{ Tropius, 49, 7000 },
		{ Metagross, 50, 15000 },
		{ Tyranitar, 55, 20000 },
		{ Smeargle, 45, 7000 },
		{ Ursaring, 45, 7000 },
		{ Shuckle, 45, 7000 },
		{ Togetic, 20, 5000 },
	};
	for (size_t i = 0; i < 48; ++i)
		tbl[ar[i].species] = ar[i];

	// Japanese games only, e-Reader. NOT SUPPORTED YET
	// ...

	return tbl;
}

static table_t generateXDShadowPkmInfoTbl(void) {
	table_t tbl;
	static const ShadowPokemonInfo ar[] = {
		{ Teddiursa, 11, 3000 },
		{ Ledyba, 10, 2500 },
		{ Poochyena, 10, 2500 },
		{ Houndour, 17, 1500 },
		{ Spheal, 17, 1500 },
		{ Baltoy, 17, 1500 },
		{ Mareep, 17, 1500 },
		{ Gulpin, 17, 1500 },
		{ Seedot, 17, 1500 },
		{ Spinarak, 14, 1500 },
		{ Numel, 14, 1500 },
		{ Carvanha, 15, 1700 },
		{ Shroomish, 15, 1800 },
		{ Delcatty, 18, 2500 },
		{ Voltorb, 19, 2500 },
		{ Makuhita, 18, 2000 },
		{ Vulpix, 18, 2000 },
		{ Duskull, 19, 2200 },
		{ Ralts, 20, 2200 },
		{ Mawile, 22, 2500 },
		{ Snorunt, 20, 2500 },
		{ Pineco, 20, 2500 },
		{ Natu, 22, 2500 },
		{ Roselia, 22, 3000 },
		{ Meowth, 22, 3500 },
		{ Swinub, 22, 2500 },
		{ Spearow, 22, 4500 },
		{ Grimer, 23, 3000 },
		{ Seel, 23, 3500 },
		{ Lunatone, 25, 5000 },
		{ Zangoose, 28, 5000 },
		{ Nosepass, 28, 4000 },
		{ Togepi, 25, 4500 },
		{ Paras, 28, 4000 },
		{ Growlithe, 28, 4000 },
		{ Shellder, 29, 4000 },
		{ Pidgeotto, 30, 4000 },
		{ Beedrill, 30, 4500 },
		{ Tangela, 30, 4000 },
		{ Butterfree, 30, 4000 },
		{ Magneton, 30, 4500 },
		{ Venomoth, 32, 4000 },
		{ Weepinbell, 32, 4000 },
		{ Arbok, 33, 5000 },
		{ Primeape, 34, 6000 },
		{ Hypno, 34, 5500 },
		{ Golduck, 33, 6500 },
		{ Sableye, 33, 7000 },
		{ Raticate, 34, 6000 },
		{ Dodrio, 34, 8000 },
		{ Farfetch_d, 36, 5500 },
		{ Altaria, 36, 6500 },
		{ Kangaskhan, 36, 6000 },
		{ Banette, 37, 7000 },
		{ Magmar, 36, 7000 },
		{ Pinsir, 35, 7000 },
		{ Magcargo, 38, 5500 },
		{ Rapidash, 40, 6000 },
		{ Hitmonchan, 38, 6000 },
		{ Hitmonlee, 38, 7000 },
		{ Lickitung, 38, 5000 },
		{ Scyther, 40, 8000 },
		{ Chansey, 39, 4000 },
		{ Solrock, 41, 7500 },
		{ Starmie, 41, 7500 },
		{ Electabuzz, 43, 7000 },
		{ Swellow, 43, 7000 },
		{ Snorlax, 43, 9000 },
		{ Poliwrath, 43, 7500 },
		{ MrMime, 43, 6500 },
		{ Dugtrio, 40, 5000 },
		{ Manectric, 44, 7000 },
		{ Salamence, 50, 9000 },
		{ Marowak, 44, 6500 },
		{ Lapras, 44, 6000 },
		{ Lugia, 50, 12000 },
		{ Zapdos, 50, 10000 },
		{ Moltres, 50, 10000 },
		{ Articuno, 50, 10000 },
		{ Tauros, 46, 9000 },
		{ Rhydon, 46, 7000 },
		{ Exeggutor, 46, 9000 },
		{ Dragonite, 55, 9000 },

	};

	for (size_t i = 0; i < 83; ++i)
		tbl[ar[i].species] = ar[i];

	return tbl;
}

const table_t colosseumTable = generateColosseumShadowPkmInfoTbl();
const table_t XDTable = generateXDShadowPkmInfoTbl();

}

namespace LibPkmGC {

ShadowPokemonInfo getShadowPokemonInfo(PokemonSpeciesIndex index, bool isXD) {
	return (isXD) ? XDTable.at(index) : colosseumTable.at(index);
}

ShadowPokemonInfo getShadowPokemonInfo(PokemonSpeciesIndex index, u8 levelMet) {
	ShadowPokemonInfo c = colosseumTable.at(index), x = XDTable.at(index);

	if (c.species == NoSpecies) return x; 
	if (x.species == NoSpecies) return c;

	if(levelMet == x.encounterLevel) return x;
	if(levelMet == c.encounterLevel) return c;

	return ShadowPokemonInfo();
}

}