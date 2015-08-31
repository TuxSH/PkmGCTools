#ifndef _LIBPKMGC_GC_POKEMON_H
#define _LIBPKMGC_GC_POKEMON_H
#include <LibPkmGC/Base/Pokemon.h>
#include <LibPkmGC/GC/Common/PokemonString.h>


#define LIBPKMGC_GC_EGG_FLAG 0
#define LIBPKMGC_GC_SECOND_ABILITY_FLAG 1
#define LIBPKMGC_GC_INVALID_POKEMON_FLAG 2

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
	/*bool hasSecondAbility(void) const;
	void setSpecialAbilityStatus(bool status);*/
	virtual PokemonAbilityIndex getAbility(void) const;
	
	u16 shadowPkmID;
	bool pkmFlags[3];

	virtual void swap(Base::Pokemon& other);
	virtual Pokemon& operator=(Base::Pokemon const& other);
protected:
	Pokemon(Pokemon const& other);
};

}
}

#endif