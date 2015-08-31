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

	virtual bool registerSpecies(PokemonSpeciesIndex index, u32 PID, u16 SID = 0, u16 TID = 0);
	virtual bool registerSpecies(Pokemon* pkm);
	void deleteEntry(size_t index);

	size_t recount(void) const;

	void sortedBySpeciesIndex(StrategyMemoEntry* dst[0x19b]); // only entries containing a valid Gen III species index are sorted
	virtual void fixInvalidEntries(void);

	u16 nbEntries;
	StrategyMemoEntry* entries[500];

protected:
	StrategyMemoData(StrategyMemoData const& other);

	virtual void deleteFields(void);
	virtual void loadFields(void);

};

}
}

#endif