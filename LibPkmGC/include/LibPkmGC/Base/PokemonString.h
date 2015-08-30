#ifndef _LIBPKMGC_BASE_POKEMONSTRING_H
#define _LIBPKMGC_BASE_POKEMONSTRING_H

#include <LibPkmGC/Core/IntegerTypes.h>
#include <algorithm>

namespace LibPkmGC {
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


protected:
	PokemonString(PokemonString const& other);

	
	mutable bool hasChanged;
	mutable char* _str;
	mutable size_t strSz, strCapacity;

	void resizeStr(void) const;
};

}
}

#endif