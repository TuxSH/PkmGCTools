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
