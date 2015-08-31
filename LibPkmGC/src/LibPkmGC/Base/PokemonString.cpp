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

#include <LibPkmGC/Base/PokemonString.h>

namespace LibPkmGC {
namespace Base {


PokemonString::PokemonString(void) : hasChanged(true), _str(NULL), strSz(0), strCapacity(0) {
}

PokemonString::~PokemonString(void) {
}

PokemonString & PokemonString::operator=(PokemonString const & other) {
	if (this != &other) {
		hasChanged = other.hasChanged;
		strSz = other.strSz;
		resizeStr();
		std::copy(other._str, other._str + strSz, _str);

	}
	return *this;
}


PokemonString::operator const char*(void) const {
	return toUTF8();
}

PokemonString::PokemonString(PokemonString const & other) : hasChanged(other.hasChanged), strSz(other.strSz), strCapacity(0), _str(NULL) {
	resizeStr();
	std::copy(other._str, other._str + strSz, _str);
}

void PokemonString::resizeStr(void) const {
	if (strCapacity < strSz) {
		strCapacity = strSz;
		delete[] _str;
		_str = new char[strSz];
	}
}

}
}
