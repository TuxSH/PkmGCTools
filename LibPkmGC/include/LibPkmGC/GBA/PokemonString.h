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

#ifndef _LIBPKMGC_GBA_POKEMON_STRING_H
#define _LIBPKMGC_GBA_POKEMON_STRING_H

#include <LibPkmGC/Base/PokemonString.h>

namespace LibPkmGC {
namespace GBA {

class LIBPKMGC_DECL PokemonString : public Base::PokemonString {
public:
	PokemonString(const char* str = NULL, bool jap = false);
	PokemonString(u8* data, size_t nb, bool jap = false);
	PokemonString(PokemonString const& other);
	~PokemonString(void);
	
	bool isGBA(void) const;
	PokemonString* clone(void) const;
	PokemonString* create(void) const;

	PokemonString& operator=(PokemonString const& other);
	PokemonString& operator=(Base::PokemonString const& other);

	void fromUTF8(const char* str = NULL);
	const char* toUTF8(void) const;

	size_t size(void) const;
	void load(u8* data, size_t nb);
	void save(u8* data, size_t nb) const;

	PokemonString(GC::PokemonString const& other);

};

}
}

#endif
