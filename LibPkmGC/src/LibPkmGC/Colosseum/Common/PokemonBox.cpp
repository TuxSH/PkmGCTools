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

#include <LibPkmGC/Colosseum/Common/PokemonBox.h>

namespace LibPkmGC {
namespace Colosseum {

PokemonBox::PokemonBox(void) : GC::PokemonBox(0x24a4) {
	initWithEmptyData();
}

PokemonBox::PokemonBox(const u8* inData) : GC::PokemonBox(0x24a4, inData) {
	load();
}
PokemonBox::PokemonBox(PokemonBox const& other) : GC::PokemonBox(other) {}


PokemonBox::~PokemonBox(void)
{
}



PokemonBox* PokemonBox::clone(void) const {
	return new PokemonBox(*this);
}

PokemonBox* PokemonBox::create(void) const {
	return new PokemonBox;
}



void PokemonBox::loadFields(void) {
	GC::PokemonBox::loadFields();
	LD_SUBSTRUCTURE_ARRAY(Pokemon, pkm, 30, 0x14);
}

void PokemonBox::save(void) {
	GC::PokemonBox::save();
	SV_SUBSTRUCTURE_ARRAY(Pokemon, pkm, 30, 0x14);
}

}
}