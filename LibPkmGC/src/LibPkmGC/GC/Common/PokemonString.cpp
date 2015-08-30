#include <LibPkmGC/GC/Common/PokemonString.h>
#include <algorithm>
#include <cstring>


namespace LibPkmGC {
namespace GC {

PokemonString::PokemonString(const char* str) : Base::PokemonString(), _data(NULL), dataSz(0), dataCapacity(0) {
	fromUTF8(str);
}

PokemonString::PokemonString(u8 * data, size_t nb) : Base::PokemonString(), _data(NULL), dataSz(0), dataCapacity(0){
	load(data, nb);
}

PokemonString::PokemonString(PokemonString const& other) : Base::PokemonString(other), dataSz(other.dataSz), dataCapacity(0), _data(NULL) {
	resizeData();
	std::copy(other._data, other._data + dataSz, _data);
}

PokemonString::~PokemonString(void) {
	delete[] _data;
}

PokemonString * PokemonString::clone(void) const {
	return new PokemonString(*this);
}

PokemonString * PokemonString::create(void) const {
	return new PokemonString;
}

PokemonString & PokemonString::operator=(PokemonString const & other) {
	if (this != &other) {
		Base::PokemonString::operator=(other);
		delete[] _data;
		std::copy(other._data, other._data + dataSz, _data);
	}
	return *this;
}

PokemonString& PokemonString::operator=(Base::PokemonString const& other) {
	return operator=((PokemonString const&)other);
}


}
}

namespace {
using namespace LibPkmGC;
typedef void* conv_t;
typedef u32 ucs4_t;

// Custom :
#define RET_ILSEQ -1
#define RET_ILUNI -2
#define RET_TOOSMALL -3
#define RET_TOOFEW(c) (-4*(c+1))

// Adapted from : 

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


/*
* UCS-2BE = UCS-2 big endian
*/

static int
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

static int
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

/*
* UTF-8
*/

/* Specification: RFC 3629 */

static int
utf8_mbtowc(conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
	unsigned char c = s[0];

	if (c < 0x80) {
		*pwc = c;
		return 1;
	}
	else if (c < 0xc2) {
		return RET_ILSEQ;
	}
	else if (c < 0xe0) {
		if (n < 2)
			return RET_TOOFEW(0);
		if (!((s[1] ^ 0x80) < 0x40))
			return RET_ILSEQ;
		*pwc = ((ucs4_t)(c & 0x1f) << 6)
			| (ucs4_t)(s[1] ^ 0x80);
		return 2;
	}
	else if (c < 0xf0) {
		if (n < 3)
			return RET_TOOFEW(0);
		if (!((s[1] ^ 0x80) < 0x40 && (s[2] ^ 0x80) < 0x40
			&& (c >= 0xe1 || s[1] >= 0xa0)))
			return RET_ILSEQ;
		*pwc = ((ucs4_t)(c & 0x0f) << 12)
			| ((ucs4_t)(s[1] ^ 0x80) << 6)
			| (ucs4_t)(s[2] ^ 0x80);
		return 3;
	}
	else if (c < 0xf8 && sizeof(ucs4_t) * 8 >= 32) {
		if (n < 4)
			return RET_TOOFEW(0);
		if (!((s[1] ^ 0x80) < 0x40 && (s[2] ^ 0x80) < 0x40
			&& (s[3] ^ 0x80) < 0x40
			&& (c >= 0xf1 || s[1] >= 0x90)))
			return RET_ILSEQ;
		*pwc = ((ucs4_t)(c & 0x07) << 18)
			| ((ucs4_t)(s[1] ^ 0x80) << 12)
			| ((ucs4_t)(s[2] ^ 0x80) << 6)
			| (ucs4_t)(s[3] ^ 0x80);
		return 4;
	}
	else if (c < 0xfc && sizeof(ucs4_t) * 8 >= 32) {
		if (n < 5)
			return RET_TOOFEW(0);
		if (!((s[1] ^ 0x80) < 0x40 && (s[2] ^ 0x80) < 0x40
			&& (s[3] ^ 0x80) < 0x40 && (s[4] ^ 0x80) < 0x40
			&& (c >= 0xf9 || s[1] >= 0x88)))
			return RET_ILSEQ;
		*pwc = ((ucs4_t)(c & 0x03) << 24)
			| ((ucs4_t)(s[1] ^ 0x80) << 18)
			| ((ucs4_t)(s[2] ^ 0x80) << 12)
			| ((ucs4_t)(s[3] ^ 0x80) << 6)
			| (ucs4_t)(s[4] ^ 0x80);
		return 5;
	}
	else if (c < 0xfe && sizeof(ucs4_t) * 8 >= 32) {
		if (n < 6)
			return RET_TOOFEW(0);
		if (!((s[1] ^ 0x80) < 0x40 && (s[2] ^ 0x80) < 0x40
			&& (s[3] ^ 0x80) < 0x40 && (s[4] ^ 0x80) < 0x40
			&& (s[5] ^ 0x80) < 0x40
			&& (c >= 0xfd || s[1] >= 0x84)))
			return RET_ILSEQ;
		*pwc = ((ucs4_t)(c & 0x01) << 30)
			| ((ucs4_t)(s[1] ^ 0x80) << 24)
			| ((ucs4_t)(s[2] ^ 0x80) << 18)
			| ((ucs4_t)(s[3] ^ 0x80) << 12)
			| ((ucs4_t)(s[4] ^ 0x80) << 6)
			| (ucs4_t)(s[5] ^ 0x80);
		return 6;
	}
	else
		return RET_ILSEQ;
}

static int
utf8_wctomb(conv_t conv, unsigned char *r, ucs4_t wc, int n) /* n == 0 is acceptable */ {
	int count;
	if (wc < 0x80)
		count = 1;
	else if (wc < 0x800)
		count = 2;
	else if (wc < 0x10000)
		count = 3;
	else if (wc < 0x200000)
		count = 4;
	else if (wc < 0x4000000)
		count = 5;
	else if (wc <= 0x7fffffff)
		count = 6;
	else
		return RET_ILUNI;
	if (n < count)
		return RET_TOOSMALL;
	switch (count) { /* note: code falls through cases! */
	case 6: r[5] = 0x80 | (wc & 0x3f); wc = wc >> 6; wc |= 0x4000000;
	case 5: r[4] = 0x80 | (wc & 0x3f); wc = wc >> 6; wc |= 0x200000;
	case 4: r[3] = 0x80 | (wc & 0x3f); wc = wc >> 6; wc |= 0x10000;
	case 3: r[2] = 0x80 | (wc & 0x3f); wc = wc >> 6; wc |= 0x800;
	case 2: r[1] = 0x80 | (wc & 0x3f); wc = wc >> 6; wc |= 0xc0;
	case 1: r[0] = wc;
	}
	return count;
}


}

namespace LibPkmGC {
namespace GC {

void PokemonString::fromUTF8(const char * str) {
	str = (str == NULL) ? "" : str;
	strSz = std::strlen(str) + 1;
	resizeStr();

	dataSz = 2 * strSz;
	resizeStr();

	dataSz = 0;

	int s = 0;
	size_t offset = 0;
	while (offset < strSz) {
		u32 c;
		s = utf8_mbtowc(NULL, &c, (const unsigned char*)str + offset, 6);
		if (s < 0) break;
		offset += s;
		s = ucs2be_wctomb(NULL, _data + dataSz, c, 2);
		if (s < 0) break;
		dataSz += s;
		if (c == 0) break;
	}
	hasChanged = true;
}

const char * PokemonString::toUTF8(void) const {
	if (!hasChanged) return _str;
	
	strSz = 3 * (dataSz / 2);
	resizeStr();

	strSz = 0;

	int s = 0;
	size_t offset = 0;

	while (offset < dataSz) {
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
	while ((2 * i < dataSz) && (_data[2 * i] != 0 || _data[2 * i + 1] != 0)) i += 2;
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

	std::fill(data + 2 * m, data + 2 * (nb + 1), 0);
}

void PokemonString::resizeData(void) {
	if (dataCapacity < dataSz) {
		dataCapacity = dataSz;
		delete[] _data;
		_data = new u8[dataSz];
	}
}


}
}