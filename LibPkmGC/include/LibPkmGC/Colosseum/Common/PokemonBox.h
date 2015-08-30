#ifndef _LIBPKMGC_COLOSSEUM_POKEMON_BOX_H
#define _LIBPKMGC_COLOSSEUM_POKEMON_BOX_H

#include <LibPkmGC/GC/Common/PokemonBox.h>
#include <LibPkmGC/Colosseum/Common/Pokemon.h>

namespace LibPkmGC {
namespace Colosseum {

class LIBPKMGC_DECL PokemonBox :
	public GC::PokemonBox
{
public:
	static const size_t size = 0x24a4;
	PokemonBox(void);
	PokemonBox(PokemonBox const& other);
	PokemonBox(const u8* inData);
	~PokemonBox(void);

	PokemonBox* clone(void) const;
	PokemonBox* create(void) const;
	
	void save(void);

	PokemonBox(XD::PokemonBox const& other);
protected:
	void loadFields(void);

};

}
}

#endif