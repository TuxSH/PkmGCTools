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

#include <LibPkmGC/XD/Common/StrategyMemoEntry.h>

namespace LibPkmGC {
namespace XD {

StrategyMemoEntry::~StrategyMemoEntry(void) {
}

StrategyMemoEntry::StrategyMemoEntry(void) : GC::StrategyMemoEntry() {
	initWithEmptyData();
}

StrategyMemoEntry::StrategyMemoEntry(const u8* inData) : GC::StrategyMemoEntry(inData) {
	load();
}

bool StrategyMemoEntry::isXD(void) const {
	return true;
}

StrategyMemoEntry* StrategyMemoEntry::clone(void) const {
	return new StrategyMemoEntry(*this);
}

StrategyMemoEntry* StrategyMemoEntry::create(void) const {
	return new StrategyMemoEntry;
}

bool StrategyMemoEntry::isInfoIncomplete(void) const{
	return false;
}

void StrategyMemoEntry::setInfoCompleteness(bool incomplete){
	flags = (species == NoSpecies) ? 0 : 2;
}

}
}