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

#ifndef _LIBPKMGC_XD_STRATEGY_MEMO_ENTRY_H
#define _LIBPKMGC_XD_STRATEGY_MEMO_ENTRY_H

#include <LibPkmGC/GC/Common/StrategyMemoEntry.h>

namespace LibPkmGC {
namespace XD {


class LIBPKMGC_DECL StrategyMemoEntry :
	public GC::StrategyMemoEntry
{
public:
	static const size_t size = 12;
	~StrategyMemoEntry(void);
	StrategyMemoEntry(void);
	StrategyMemoEntry(const u8* inData);

	bool isXD(void) const;
	StrategyMemoEntry* clone(void) const;
	StrategyMemoEntry* create(void) const;

	bool isInfoPartial(void) const;
	void setInfoCompleteness(bool partial);
};

}
}

#endif