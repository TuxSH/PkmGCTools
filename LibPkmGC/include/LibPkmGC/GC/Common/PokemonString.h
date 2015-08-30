#ifndef _LIBPKMGC_GC_POKEMON_STRING_H
#define _LIBPKMGC_GC_POKEMON_STRING_H

#include <LibPkmGC/Base/PokemonString.h>

namespace LibPkmGC {
namespace GC {

class LIBPKMGC_DECL PokemonString : public Base::PokemonString {
public:
	PokemonString(const char* str = NULL);
	PokemonString(u8* data, size_t nb);
	PokemonString(PokemonString const& other);
	~PokemonString(void);
	
	PokemonString* clone(void) const;
	PokemonString* create(void) const;

	PokemonString& operator=(PokemonString const& other);
	PokemonString& operator=(Base::PokemonString const& other);

	void fromUTF8(const char* str = NULL);
	const char* toUTF8(void) const;

	size_t size(void) const;
	void load(u8* data, size_t nb);
	void save(u8* data, size_t nb) const;

private:
	u8* _data;
	size_t dataSz;
	size_t dataCapacity;

	void resizeData(void);
};

}
}

#endif
