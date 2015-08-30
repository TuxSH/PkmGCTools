#ifndef _LIBPKMGC_GC_POKEMON_BOX_H
#define _LIBPKMGC_GC_POKEMON_BOX_H

#include <LibPkmGC/Base/PokemonBox.h>
#include <LibPkmGC/GC/Common/Pokemon.h>

namespace LibPkmGC {
namespace GC {

/*
	0x00: PokemonString name (2*(8+1) bytes)
	0x12: u16 ??
	0x14 -- end: Pokemon pkm[30]
*/

class LIBPKMGC_DECL PokemonBox : public Base::PokemonBox {
public:
	PokemonBox(size_t inSize, const u8* inData = NULL);
	virtual ~PokemonBox(void);

	virtual PokemonBox* clone(void) const = 0;
	virtual PokemonBox* create(void) const = 0;

	virtual void save(void);
	
protected:
	PokemonBox(PokemonBox const& other);
	virtual void loadFields(void);
};

}
}

#endif