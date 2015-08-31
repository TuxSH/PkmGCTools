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

#ifndef _LIBPKMGC_GC_POKEMON_BOX_H
#define _LIBPKMGC_GC_POKEMON_BOX_H

#include <LibPkmGC/Base/PokemonBox.h>
#include <LibPkmGC/GC/Common/Pokemon.h>

namespace LibPkmGC {
namespace GC {

/*
	0x00: PokemonString name (2*(8+1) bytes)
	0x12: u16 ??
	0x14 -- end: Pokemon pkm[30]
*/

class LIBPKMGC_DECL PokemonBox : public Base::PokemonBox {
public:
	PokemonBox(size_t inSize, const u8* inData = NULL);
	virtual ~PokemonBox(void);

	virtual PokemonBox* clone(void) const = 0;
	virtual PokemonBox* create(void) const = 0;

	virtual void save(void);
	
protected:
	PokemonBox(PokemonBox const& other);
	virtual void loadFields(void);
};

}
}

#endif