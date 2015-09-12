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

#include <LibPkmGC/Colosseum/SaveEditing/Save.h>
#include <LibPkmGC/XD/SaveEditing/Save.h>
#include <LibPkmGC/GBA/Pokemon.h>

namespace LibPkmGC {

LIBPKMGC_GEN_CONVERTER_CTOR(DaycareData)
LIBPKMGC_GEN_CONVERTER_CTOR_W_GBA(Pokemon)
LIBPKMGC_GEN_CONVERTER_CTOR(StrategyMemoData)
LIBPKMGC_GEN_CONVERTER_CTOR(PokemonBox)

namespace GBA {

PokemonString::PokemonString(GC::PokemonString const& other) : Base::PokemonString() {
	fromUTF8(other.toUTF8());
}

void Pokemon::swap(Base::Pokemon & other) {
	if (LIBPKMGC_IS_GBA(Pokemon, &other)) swap((Pokemon&)other);
	else {
		GC::Pokemon& gco = static_cast<GC::Pokemon&>(other);
		//bool inval = (GCFlags & 1) != 0; by default always true until the Pkm is traded to Colo/XD
		bool inval = !checkChecksum(false);
		u8 GCUnk = GCFlags >> 3;
		Base::Pokemon::swap(other);
		std::swap(GCUnk, gco.GCUnk);
		std::swap(inval, gco.pkmFlags[LIBPKMGC_GC_INVALID_POKEMON_FLAG]);
		bool tradedFromColoXD = true;
		bool flgs[] = { _egg, inval, tradedFromColoXD };
		if (GCUnk > 31) GCUnk = 31;
		GCFlags = GCUnk << 3;
		for (size_t i = 0; i < 3; ++i)
			GCFlags |= flgs[i] << (2 - i);
	}
}

Pokemon& Pokemon::operator=(Base::Pokemon const& other) {
	if (LIBPKMGC_IS_GBA(Pokemon, &other)) return operator=((Pokemon const&)other);
	else {
		if (this == &other) return *this;
		deleteFields();
		_flags = 1;
		initWithEmptyData(1);
		Base::Pokemon::operator=(other);

		GC::Pokemon const& gco = static_cast<GC::Pokemon const&>(other);
		bool tradedFromColoXD = true;
		bool flgs[] = { _egg, gco.pkmFlags[LIBPKMGC_GC_INVALID_POKEMON_FLAG], tradedFromColoXD };
		
		GCFlags = gco.GCUnk << 3;
		for (size_t i = 0; i < 3; ++i)
			GCFlags |= flgs[i] << (2 - i);
		return *this;
	}
}

Pokemon::Pokemon(GC::Pokemon const& other) : Base::Pokemon(100) {
	_flags = 1;
	initWithEmptyData(1);
	*this = other;
}
}

namespace GC {

PokemonString::PokemonString(GBA::PokemonString const& other) : Base::PokemonString(){
	fromUTF8(other.toUTF8());
}

Pokemon& Pokemon::operator=(Base::Pokemon const& other) {
	if (LIBPKMGC_IS_GBA(Pokemon, &other)) {
		if (this == &other) return *this;
		deleteFields();
		initWithEmptyData();
		Base::Pokemon::operator=(other);
		GBA::Pokemon const& gbao = static_cast<GBA::Pokemon const&>(other);
		GCUnk = gbao.GCFlags >> 3;
		pkmFlags[LIBPKMGC_GC_INVALID_POKEMON_FLAG] = !(((GBA::Pokemon&)(other)).checkChecksum(false));
		return *this;
	}
	else return operator=((Pokemon const&)other);
}

void Pokemon::swap(Base::Pokemon& other) {
	if (LIBPKMGC_IS_GBA(Pokemon, &other))
		static_cast<GBA::Pokemon&>(other).swap(*this);
	else
		swap((Pokemon&)other);
}


}
}