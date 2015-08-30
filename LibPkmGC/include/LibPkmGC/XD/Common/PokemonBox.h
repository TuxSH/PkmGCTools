#ifndef _LIBPKMGC_XD_POKEMON_BOX_H
#define _LIBPKMGC_XD_POKEMON_BOX_H

#include <LibPkmGC/GC/Common/PokemonBox.h>
#include <LibPkmGC/XD/Common/Pokemon.h>

namespace LibPkmGC {
namespace XD {

class LIBPKMGC_DECL PokemonBox :
	public GC::PokemonBox
{
public:
	static const size_t size = 0x170c;
	PokemonBox(void);
	PokemonBox(PokemonBox const& other);
	PokemonBox(const u8* inData);
	~PokemonBox(void);

	PokemonBox* clone(void) const;
	PokemonBox* create(void) const;
	
	void save(void);

	PokemonBox(Colosseum::PokemonBox const& other);
protected:
	void loadFields(void);
};

}
}

#endif