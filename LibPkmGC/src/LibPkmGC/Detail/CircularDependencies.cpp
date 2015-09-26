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
LIBPKMGC_GEN_CONVERTER_CTOR(TrainerData)
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
		Base::Pokemon::swap(other);
		setTradedFromGCFlag(true);
		GCFlags &= 7;
		if (GCUnk > 31) GCUnk = 31;
		GCFlags |= GCUnk << 3;
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

		setTradedFromGCFlag(true);
		GCFlags &= 7;
		if (GCUnk > 31) GCUnk = 31;
		GCFlags |= GCUnk << 3;
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
		if (GCUnk > 31) GCUnk = 31;
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