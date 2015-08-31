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