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

#ifndef _LIBPKMGC_COLOSSEUM_STRATEGY_MEMO_DATA_H
#define _LIBPKMGC_COLOSSEUM_STRATEGY_MEMO_DATA_H

#include <LibPkmGC/GC/Common/StrategyMemoData.h>
#include <LibPkmGC/Colosseum/Common/StrategyMemoEntry.h>

namespace LibPkmGC {
namespace Colosseum {

class LIBPKMGC_DECL StrategyMemoData :
	public GC::StrategyMemoData
{
public:
	static const size_t size = 0x1774;
	~StrategyMemoData(void);
	bool isXD(void) const;

	StrategyMemoData(void);
	StrategyMemoData(const u8* inData);
	StrategyMemoData(StrategyMemoData const& other);

	StrategyMemoData* clone(void) const;
	StrategyMemoData* create(void) const;

	void save(void);

	StrategyMemoData(GC::StrategyMemoData const& other);
	StrategyMemoData(XD::StrategyMemoData const& other);
protected:
	void loadFields(void);
};

}
}

#endif