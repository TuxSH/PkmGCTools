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

#ifndef _LIBPKMGC_GBA_POKEMON_H
#define _LIBPKMGC_GBA_POKEMON_H
#include <LibPkmGC/Base/Pokemon.h>
#include <LibPkmGC/GBA/PokemonString.h>


namespace LibPkmGC {
namespace GBA {
class LIBPKMGC_DECL Pokemon :
	public Base::Pokemon {
public:
	static const size_t size = 100;
	Pokemon(const u8* inData, u32 flags = 0);
	static Pokemon* load80(const u8* inData, u32 flags = 0);
	Pokemon(void);
	Pokemon(Pokemon const& other);
	~Pokemon(void);
	Pokemon* clone(void) const;
	Pokemon* create(void) const;

	bool checkChecksum(bool fix = false);
	bool isEmptyOrInvalid(void) const;
	void save(void);
	void saveEncrypted(u8* outData);

	void swap(Pokemon& other);
	Pokemon& operator=(Pokemon const& other);
	bool hasSecondAbility(void) const;
	void setSecondAbilityFlag(bool status);
	bool isEgg(void) const;
	void setEggFlag(bool status);
	bool isMarkedAsInvalid(void) const;
	void setInvalidPokemonFlag(bool flag);

	bool isTradedFromGC(void) const;
	void setTradedFromGCFlag(bool flag);


	void swap(Base::Pokemon& other);
	Pokemon& operator=(Base::Pokemon const& other);
	Pokemon(GC::Pokemon const& other);
	Pokemon(Base::Pokemon const& other);

	void reload(const u8* data = NULL, u32 inFlags = 0);

	u16 checksum;
	u8 GCFlags;

protected:
	void load(u32 flags = 0);
	void loadData(u32 flags = 0);
	void loadFields(void);

private:
	u32 _flags;
	bool _egg, _secondAbility, _invalid, _tradedFromGC;

	void decryptOrEncrypt(u8* outData);
};

}
}

#endif