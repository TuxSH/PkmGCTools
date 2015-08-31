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

#include <LibPkmGC/XD/Common/StrategyMemoData.h>

namespace LibPkmGC {
namespace XD {

StrategyMemoData::StrategyMemoData(void) : GC::StrategyMemoData(0x1774) {
	initWithEmptyData();
}

StrategyMemoData::StrategyMemoData(const u8* inData) : GC::StrategyMemoData(0x1774, inData) {
	load();
}

StrategyMemoData::StrategyMemoData(StrategyMemoData const& other) : GC::StrategyMemoData(other) {}


bool StrategyMemoData::isXD(void) const {
	return true;
}

StrategyMemoData* StrategyMemoData::clone(void) const
{
	return new StrategyMemoData(*this);
}

StrategyMemoData* StrategyMemoData::create(void) const
{
	return new StrategyMemoData;
}

void StrategyMemoData::loadFields(void) {
	GC::StrategyMemoData::loadFields();
	LD_SUBSTRUCTURE_ARRAY(StrategyMemoEntry, entries, 500, 4);
}

void StrategyMemoData::save(void) {
	GC::StrategyMemoData::save();
	SV_SUBSTRUCTURE_ARRAY(StrategyMemoEntry, entries, 500, 4);

}


StrategyMemoData::~StrategyMemoData(void)
{
}

}
}