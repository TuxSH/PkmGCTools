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

#ifndef _LIBPKMGC_BASE_POKEMON_BOX_H
#define _LIBPKMGC_BASE_POKEMON_BOX_H

#include <LibPkmGC/Base/Pokemon.h>

namespace LibPkmGC {

LIBPKMGC_FWD_DECL_GC_CLS(PokemonBox)

namespace Base {

class LIBPKMGC_DECL PokemonBox : public Base::DataStruct {
public:
	PokemonBox(size_t inSize, const u8* inData = NULL);
	virtual ~PokemonBox(void);

	virtual PokemonBox* clone(void) const = 0;
	virtual PokemonBox* create(void) const = 0;

	virtual void deleteFields(void);

	void swap(PokemonBox & other);
	PokemonBox& operator=(PokemonBox const& other);

	PokemonString *name;
	Pokemon* pkm[30];

protected:
	PokemonBox(PokemonBox const& other);

};

}
}

#endif 