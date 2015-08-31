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

#include <LibPkmGC/Base/PokemonBox.h>

namespace LibPkmGC {
namespace Base {

PokemonBox::PokemonBox(size_t inSize, const u8* inData) : DataStruct(inSize, inData) {

}

void PokemonBox::deleteFields(void) {
	for (size_t i = 0; i < 30; ++i)
		delete pkm[i];
}

PokemonBox::PokemonBox(PokemonBox const& other) : DataStruct(other) {
	CL(name);
	CL_ARRAY(pkm, 30);
}

PokemonBox::~PokemonBox(void) {
	PokemonBox::deleteFields();
}

void PokemonBox::swap(PokemonBox& other) {
	DataStruct::swap(other);
	SW(name);
	for (size_t i = 0; i < 30; ++i) pkm[i]->swap(*other.pkm[i]);
}

PokemonBox& PokemonBox::operator=(PokemonBox const& other) {
	DataStruct::operator=(other);
	if (this != &other) {
		PokemonBox::deleteFields();
		for (size_t i = 0; i < 30; ++i) *pkm[i] = *(other.pkm[i]);
		CL(name);
	}
	return *this;
}

}
}