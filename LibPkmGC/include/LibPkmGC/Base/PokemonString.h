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

#ifndef _LIBPKMGC_BASE_POKEMONSTRING_H
#define _LIBPKMGC_BASE_POKEMONSTRING_H

#include <LibPkmGC/Core/IntegerTypes.h>
#include <algorithm>

#if defined(LIBPKMGC_SOURCE) && !defined(RET_ILSEQ)
/* Return code if invalid. (xxx_mbtowc) */
# define RET_ILSEQ      -1
/* Return code if no bytes were read. (xxx_mbtowc) */
//# define RET_TOOFEW     -2
# define RET_TOOFEW(c)     -2

/* Return code if invalid. (xxx_wctomb) */
# define RET_ILUNI      -1
/* Return code if output buffer is too small. (xxx_wctomb, xxx_reset) */
# define RET_TOOSMALL   -2

#endif


namespace LibPkmGC {

namespace Detail {

typedef void* conv_t;
typedef u32 ucs4_t;
int ucs2be_mbtowc(conv_t conv, ucs4_t *pwc, const unsigned char *s, int n);
int ucs2be_wctomb(conv_t conv, unsigned char *r, ucs4_t wc, int n);
int utf8_mbtowc(conv_t conv, ucs4_t *pwc, const unsigned char *s, int n);
int utf8_wctomb(conv_t conv, unsigned char *r, ucs4_t wc, int n);

int pkmgba_mbtowc(conv_t conv, ucs4_t *pwc, const unsigned char* s, int n, bool jap = false);
int pkmgba_wctomb(conv_t conv, unsigned char *r, ucs4_t wc, int n, bool jap = false);

}


namespace GC { class PokemonString; } namespace GBA { class PokemonString;  }

namespace Base {

// Commands (scroll, color etc...) are NOT supported
class LIBPKMGC_DECL PokemonString {
public:
	PokemonString(void);
	virtual ~PokemonString(void);
	virtual PokemonString& operator=(PokemonString const& other);

	virtual PokemonString* clone(void) const = 0;
	virtual PokemonString* create(void) const = 0;

	virtual void fromUTF8(const char* str = NULL) = 0;

	virtual const char* toUTF8(void) const = 0;
	virtual size_t size(void) const = 0; // number of characters, not counting NULL

	operator const char*(void) const;

	virtual void load(u8* data, size_t nb) = 0; // nb: number of characters, not counting NULL
	virtual void save(u8* data, size_t nb) const = 0;

	virtual bool isGBA(void) const = 0;

	bool usesJapaneseCharset(void) const;
	void setCharset(bool jap);
protected:
	bool _japanese;
	PokemonString(PokemonString const& other);

	
	mutable bool hasChanged;
	mutable char* _str;
	mutable size_t strSz, strCapacity;

	void resizeStr(void) const;

	u8* _data;

	size_t dataSz;
	size_t dataCapacity;

	void resizeData(void);
};

}
}

#endif