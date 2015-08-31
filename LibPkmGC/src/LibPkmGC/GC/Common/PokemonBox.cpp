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

#include <LibPkmGC/GC/Common/PokemonBox.h>

namespace LibPkmGC {
namespace GC {

PokemonBox::PokemonBox(size_t inSize, const u8* inData) : Base::PokemonBox(inSize, inData){
};

PokemonBox::~PokemonBox(void) {
}

PokemonBox::PokemonBox(PokemonBox const& other) : Base::PokemonBox(other) {

}
void PokemonBox::loadFields(void) {
	name = new PokemonString(data, 8);
}

void PokemonBox::save(void) {
	name->save(data, 8);
}

}
}