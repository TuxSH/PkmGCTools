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

// This file uses code from libiconv : 

/*
* Copyright (C) 1999-2001, 2004 Free Software Foundation, Inc.
* This file is part of the GNU LIBICONV Library.
*
* The GNU LIBICONV Library is free software; you can redistribute it
* and/or modify it under the terms of the GNU Library General Public
* License as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* The GNU LIBICONV Library is distributed in the hope that it will be
* useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Library General Public License for more details.
*
* You should have received a copy of the GNU Library General Public
* License along with the GNU LIBICONV Library; see the file COPYING.LIB.
* If not, write to the Free Software Foundation, Inc., 51 Franklin Street,
* Fifth Floor, Boston, MA 02110-1301, USA.
*/


#include <LibPkmGC/GC/Common/PokemonString.h>
#include <algorithm>
#include <cstring>


using namespace LibPkmGC::Detail;

namespace LibPkmGC {
namespace GC {

PokemonString::PokemonString(const char* str) : Base::PokemonString() {
	fromUTF8(str);
}

PokemonString::PokemonString(u8 * data, size_t nb) : Base::PokemonString(){
	load(data, nb);
}

PokemonString::PokemonString(PokemonString const& other) : Base::PokemonString(other) {
}

PokemonString::~PokemonString(void) {
}

bool PokemonString::isGBA(void) const {
	return false;
}

PokemonString * PokemonString::clone(void) const {
	return new PokemonString(*this);
}

PokemonString * PokemonString::create(void) const {
	return new PokemonString;
}

PokemonString & PokemonString::operator=(PokemonString const & other) {
	return (PokemonString&) Base::PokemonString::operator=(other);
}

PokemonString& PokemonString::operator=(Base::PokemonString const& other) {
	if (other.isGBA()) {
		_japanese = other.usesJapaneseCharset();
		fromUTF8(other.toUTF8());
		return *this;
	}
	else return operator=((PokemonString const&)other);
}


}
}

namespace LibPkmGC { namespace Detail {

// Adapted from libiconv (see license above)


/*
* UCS-2BE = UCS-2 big endian
*/

int
ucs2be_mbtowc(conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
	if (n >= 2) {
		if (s[0] >= 0xd8 && s[0] < 0xe0) {
			return RET_ILSEQ;
		}
		else if (s[0] == 0xff && s[1] == 0xff) { // [LibPkmGC]
			return RET_ILSEQ;
		}
		else {
			*pwc = (s[0] << 8) + s[1];
			return 2;
		}
	}
	return RET_TOOFEW(0);
}

int
ucs2be_wctomb(conv_t conv, unsigned char *r, ucs4_t wc, int n)
{
	if (wc < 0x10000 && !(wc >= 0xd800 && wc < 0xe000) && wc != 0xffff) { // [LibPkmGC]
		if (n >= 2) {
			r[0] = (unsigned char)(wc >> 8);
			r[1] = (unsigned char)wc;
			return 2;
		}
		else
			return RET_TOOSMALL;
	}
	return RET_ILUNI;
}


}
}


namespace LibPkmGC {
namespace GC {

void PokemonString::fromUTF8(const char * str) {
	str = (str == NULL) ? "" : str;
	strSz = std::strlen(str) + 1;
	resizeStr();

	dataSz = 2 * strSz;
	resizeData();

	dataSz = 0;

	int s = 0;
	size_t offset = 0;
	while (offset < strSz - 1) {
		u32 c;
		s = utf8_mbtowc(NULL, &c, (const unsigned char*)str + offset, 6);
		if (s < 0) break;
		offset += s;
		if (c == 0) break;
		s = ucs2be_wctomb(NULL, _data + dataSz, c, 2);
		if (s < 0) break;
		dataSz += s;
	}
	assert(dataSz % 2 == 0);
	_data[dataSz++] = 0;
	_data[dataSz++] = 0;
	hasChanged = true;
}

const char * PokemonString::toUTF8(void) const {
	if (!hasChanged) return _str;
	assert(dataSz % 2 == 0);

	strSz = 3 * (dataSz / 2);
	resizeStr();

	strSz = 0;

	int s = 0;
	size_t offset = 0;

	while (offset < dataSz) {
		assert(strSz < 3 * (dataSz / 2));

		u32 c;
		s = ucs2be_mbtowc(NULL, &c, (const unsigned char*)_data + offset, 2);
		if (s < 0) break;
		offset += s;
		s = utf8_wctomb(NULL, (unsigned char*) _str + strSz, c, 6);
		if (s < 0) break;
		strSz += s;
		if (c == 0) break;
	}
	hasChanged = false;
	return _str;
}

size_t PokemonString::size(void) const {
	size_t i = 0;
	while ((2 * i < dataSz) && (_data[2 * i] != 0 || _data[2 * i + 1] != 0)) ++i;
	return i;
}


void PokemonString::load(u8 * data, size_t nb) {
	dataSz = 2 * nb + 2;
	resizeData();
	std::copy(data, data + dataSz, _data);
}

void PokemonString::save(u8 * data, size_t nb) const {
	size_t sz = size(), m = ((nb <= sz) ? nb : sz); // how much characters should we write ?
	std::copy(_data, _data + 2*m, data);

	if(m <= nb)
		std::fill(data + 2 * m, data + 2 * (nb + 1), 0);
}


}
}