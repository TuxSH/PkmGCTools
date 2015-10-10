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

#ifndef _LIBPKMGC_GC_STRATEGY_MEMO_DATA_H
#define _LIBPKMGC_GC_STRATEGY_MEMO_DATA_H

#include <LibPkmGC/GC/Common/StrategyMemoEntry.h>
#include <LibPkmGC/GC/Common/Pokemon.h>

namespace LibPkmGC {

LIBPKMGC_FWD_DECL_GC_CLS(StrategyMemoData)

namespace GC {

/*
	For both XD and Colosseum:
	0x00: u32 nbEntries, max. 500
	0x04: StrategyMemoEntry entries[500];
*/

class LIBPKMGC_DECL StrategyMemoData :
	public Base::DataStruct
{
public:
	StrategyMemoData(size_t inSize, const u8* inData = NULL);

	virtual bool isXD(void) const = 0;
	virtual ~StrategyMemoData(void);

	virtual StrategyMemoData* clone(void) const = 0;
	virtual StrategyMemoData* create(void) const = 0;

	void swap(StrategyMemoData& other);
	StrategyMemoData& operator=(StrategyMemoData const& other);

	virtual void save(void);

	virtual size_t registerSpecies(PokemonSpeciesIndex index, u32 PID, u16 SID = 0, u16 TID = 0);
	virtual size_t registerSpecies(Pokemon* pkm);
	void deleteEntry(size_t index);

	size_t recount(void) const;

	void sortedBySpeciesIndex(StrategyMemoEntry* dst[0x19d]); // only entries containing a valid Gen III species index are sorted
	virtual void fixInvalidEntries(StrategyMemoEntry** dst = NULL);

	void setInfoCompletenessForAll(bool incomplete);
	u16 nbEntries;
	StrategyMemoEntry* entries[500];

protected:
	StrategyMemoData(StrategyMemoData const& other);

	virtual void deleteFields(void);
	virtual void loadFields(void);

public:
	template<typename RNGType>
	void clearMemo(RNGType& rng) {
		nbEntries = 0;
		for (size_t i = 0; i < 500; ++i) {
			entries[i]->species = NoSpecies;
			entries[i]->flags = 0;
			entries[i]->generateRandomPID(rng);
		}
	}

	template<typename RNGType>
	void fillMemo(RNGType& rng, bool allShiny = false) {
		allShiny = allShiny && !isXD();
		StrategyMemoEntry* bySpecies[0x19d];
		fixInvalidEntries(bySpecies);
		for (PokemonSpeciesIndex i = NoSpecies; i <= Chimecho; i = (PokemonSpeciesIndex)(i+1)) {
			size_t index = (size_t)i;
			if (!getSpeciesData(i).isValid) continue; 
			if (bySpecies[i] == NULL) {
				StrategyMemoEntry *entry = entries[nbEntries++];
				bySpecies[i] = entry;
				entry->species = i;
				entry->firstTID = (u16)((u32)rng() >> 16);
				entry->firstSID = (u16)((u32)rng() >> 16);
				entries[nbEntries]->generateRandomPID(rng);
			}
			StrategyMemoEntry *entry = bySpecies[i];
			if (allShiny) entry->firstSID = entry->firstTID ^ (entry->firstPID >> 16) ^ (entry->firstPID & 0xffff);
		}

		setInfoCompletenessForAll(false);
	}


};

}
}

#endif