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

#ifndef _LIBPKMGC_XD_POKEMON_BOX_H
#define _LIBPKMGC_XD_POKEMON_BOX_H

#include <LibPkmGC/GC/Common/PokemonBox.h>
#include <LibPkmGC/XD/Common/Pokemon.h>

namespace LibPkmGC {
namespace XD {

class LIBPKMGC_DECL PokemonBox :
	public GC::PokemonBox
{
public:
	static const size_t size = 0x170c;
	PokemonBox(void);
	PokemonBox(PokemonBox const& other);
	PokemonBox(const u8* inData);
	~PokemonBox(void);

	PokemonBox* clone(void) const;
	PokemonBox* create(void) const;
	
	void save(void);

	PokemonBox(Base::PokemonBox const& other);
	PokemonBox(GC::PokemonBox const& other);
	PokemonBox(Colosseum::PokemonBox const& other);
protected:
	void loadFields(void);
};

}
}

#endif