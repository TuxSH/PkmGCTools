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