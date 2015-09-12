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

#include <LibPkmGC/GBA/PokemonString.h>
#include <LibPkmGC/GBA/Detail/GBACharTables.h>
#include <algorithm>
#include <cstring>

using namespace LibPkmGC::Detail;

namespace LibPkmGC {
namespace GBA {

PokemonString::PokemonString(const char* str, bool jap) : Base::PokemonString() {
	_japanese = jap;
	fromUTF8(str);
}

PokemonString::PokemonString(u8 * data, size_t nb, bool jap) : Base::PokemonString() {
	_japanese = jap;
	load(data, nb);
}

PokemonString::PokemonString(PokemonString const& other) : Base::PokemonString(other) {
}

PokemonString::~PokemonString(void) {
}

bool PokemonString::isGBA(void) const {
	return true;
}

PokemonString * PokemonString::clone(void) const {
	return new PokemonString(*this);
}

PokemonString * PokemonString::create(void) const {
	return new PokemonString;
}

PokemonString & PokemonString::operator=(PokemonString const & other) {
	return (PokemonString&)Base::PokemonString::operator=(other);
}

PokemonString& PokemonString::operator=(Base::PokemonString const& other) {
	if (!other.isGBA()) {
		_japanese = other.usesJapaneseCharset();

		fromUTF8(other.toUTF8());
		return *this;
	}
	else return operator=((PokemonString const&)other);
}


}
}

namespace LibPkmGC {
namespace Detail {

int pkmgba_mbtowc(conv_t conv, ucs4_t *pwc, const unsigned char* s, int n, bool jap) {
	if (n < 1) return RET_TOOFEW(0);

	if (*s == 0xff) *pwc = 0;
	else if (*s >= 0xf7 && *s <= 0xfe) return RET_ILSEQ; // commands
	else *pwc = GBAToUCS4(*s, jap);

	return 1;
}

int pkmgba_wctomb(conv_t conv, unsigned char *r, ucs4_t wc, int n, bool jap) {
	if (n < 1) return RET_TOOSMALL;

	if (wc == 0) *r = 0xff;
	else *r = UCS4ToGBA(wc, jap);

	return 1;
}




}
}


namespace LibPkmGC {
namespace GBA {

void PokemonString::fromUTF8(const char * str) {
	str = (str == NULL) ? "" : str;
	strSz = std::strlen(str) + 1;
	resizeStr();

	dataSz = strSz;
	resizeData();

	dataSz = 0;

	int s = 0;
	size_t offset = 0;
	while (offset < strSz - 1) {
		u32 c;
		s = utf8_mbtowc(NULL, &c, (const unsigned char*)str + offset, strSz - 1);
		if (s < 0) break;
		offset += s;
		if (c == 0) break;
		s = pkmgba_wctomb(NULL, _data + dataSz, c, 2, _japanese);
		if (s < 0) break;
		dataSz += s;
	}
	_data[dataSz++] = 0xff;
	hasChanged = true;
}

const char * PokemonString::toUTF8(void) const {
	if (!hasChanged) return _str;

	strSz = 3 * dataSz + 3;
	resizeStr();

	strSz = 0;

	int s = 0;
	size_t offset = 0;

	while (offset < dataSz) {
		u32 c;
		s = pkmgba_mbtowc(NULL, &c, (const unsigned char*)_data + offset, 2, _japanese);
		if (s < 0) break;
		offset += s;
		if (c == 0) break;
		s = utf8_wctomb(NULL, (unsigned char*)_str + strSz, c, 6);
		if (s < 0) break;
		strSz += s;
	}
	_str[strSz++] = 0;
	hasChanged = false;
	return _str;
}

size_t PokemonString::size(void) const {
	size_t i = 0;
	while ((i < dataSz) && (_data[i] != 0xff)) ++i;
	return i;
}

void PokemonString::load(u8 * data, size_t nb) {
	dataSz = nb;
	resizeData();
	std::copy(data, data + dataSz, _data);
}

void PokemonString::save(u8 * data, size_t nb) const {
	size_t sz = size(), m = ((nb <= sz) ? nb : sz); // how much characters should we write ?
	std::copy(_data, _data + m, data);
	if (sz < nb) {
		data[sz] = 0xff;
		if(sz+1 < nb) std::fill(data + sz + 1, data + nb, 0);
	}
}


}
}