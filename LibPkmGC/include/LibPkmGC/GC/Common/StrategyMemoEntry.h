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

#ifndef _LIBPKMGC_GC_STRATEGY_MEMO_ENTRY_H
#define _LIBPKMGC_GC_STRATEGY_MEMO_ENTRY_H

#include <LibPkmGC/Base/DataStruct.h>
#include <LibPkmGC/Core/PokemonInfo.h>


namespace LibPkmGC {

LIBPKMGC_FWD_DECL_GC_CLS(StrategyMemoEntry)

namespace GC {

/*
	For both Colosseum and XD:
	0x00: u16 pokemonIndex | flag (Colosseum: 0 : pokémon fully registered; 0x8000 : registered as seen; XD : 0x8000 if registered)
	0x04: u16 firstSID
	0x06: u16 firstTID
	0x08: u32 firstPID
*/

class LIBPKMGC_DECL StrategyMemoEntry :
	public Base::DataStruct
{
public:
	StrategyMemoEntry(const u8* inData = NULL);
	virtual ~StrategyMemoEntry(void);
	virtual bool isXD(void) const = 0;
	virtual void save(void);

	virtual StrategyMemoEntry* clone(void) const = 0;
	virtual StrategyMemoEntry* create(void) const = 0;

	void swap(StrategyMemoEntry& other);

	bool isEmpty(void) const;
	bool isShiny(void) const;

	template<typename RNGType>
	void generateRandomPID(RNGType& rng) {
		firstPID = (((u32)rng() >> 16) | (((u32)rng() >> 16) << 16)) % 0xffffffff; // <-- no & 0xffff here
	}


	virtual bool isInfoIncomplete(void) const = 0;
	virtual void setInfoCompleteness(bool incomplete) = 0;


	u16 flags;
	PokemonSpeciesIndex species;
	u16 firstSID, firstTID;
	u32 firstPID;

protected:
	virtual void deleteFields(void);
	virtual void loadFields(void);
};

}
}

#endif