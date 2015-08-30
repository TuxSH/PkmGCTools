#ifndef _LIBPKMGC_GC_POKEMON_H
#define _LIBPKMGC_GC_POKEMON_H
#include <LibPkmGC/Base/Pokemon.h>
#include <LibPkmGC/GC/Common/PokemonString.h>

namespace LibPkmGC {
namespace GC {
class LIBPKMGC_DECL Pokemon :
	public Base::Pokemon {
public:
	Pokemon(size_t inSize, const u8* inData = NULL);
	virtual ~Pokemon(void);
	virtual Pokemon* clone(void) const = 0;
	virtual Pokemon* create(void) const = 0;

	virtual void swap(Pokemon& other);
	virtual Pokemon& operator=(Pokemon const& other);
	virtual bool hasSpecialAbility(void) const = 0;
	virtual void setSpecialAbilityStatus(bool status) = 0;
	virtual PokemonAbilityIndex getAbility(void) const;
	u16 shadowPkmID;

	virtual void swap(Base::Pokemon& other);
	virtual Pokemon& operator=(Base::Pokemon const& other);
protected:
	Pokemon(Pokemon const& other);
};

}
}

#endif