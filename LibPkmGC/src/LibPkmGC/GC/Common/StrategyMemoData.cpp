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

#include <LibPkmGC/GC/Common/StrategyMemoData.h>
namespace LibPkmGC {
namespace GC {

StrategyMemoData::StrategyMemoData(size_t inSize, const u8* inData) : Base::DataStruct(inSize, inData) {
}

void StrategyMemoData::deleteFields(void) {
	for (size_t i = 0; i < 500; ++i)
		delete entries[i];
}

StrategyMemoData::~StrategyMemoData(void) {
	StrategyMemoData::deleteFields();
}

StrategyMemoData::StrategyMemoData(StrategyMemoData const& other) : nbEntries(other.nbEntries) {
	CL_ARRAY(entries, 500);
}

void StrategyMemoData::swap(StrategyMemoData& other) {
	Base::DataStruct::swap(other);
	SW(nbEntries);
	SW_ARRAY(entries, 500);
}

StrategyMemoData& StrategyMemoData::operator=(StrategyMemoData const& other) {
	Base::DataStruct::operator=(other);
	if (this != &other) {
		for (size_t i = 0; i < 500; ++i) *entries[i] = *(other.entries[i]);
	}
	return *this;
}

void StrategyMemoData::loadFields(void) {
	LD_FIELD(u16, nbEntries, 0);
	//if (nbEntries > 0x1f4) nbEntries = 0x1f4;
}

void StrategyMemoData::save(void) {
	//if (nbEntries > 0x1f4) nbEntries = 0x1f4;
	SV_FIELD(u16, nbEntries, 0);
}

size_t StrategyMemoData::registerSpecies(PokemonSpeciesIndex index, u32 PID, u16 SID, u16 TID) {
	u16 i = 0;

	if (!getSpeciesData(index).isValid) return 501;
	while (i < nbEntries && index != NoSpecies && index != entries[i++]->species);
	if (i == nbEntries || nbEntries == 500) return 501;

	i = ++nbEntries - 1;
	StrategyMemoEntry* entry = entries[i];

	entry->setInfoCompleteness(true);
	entry->species = index;
	entry->firstSID = SID;
	entry->firstTID = TID;
	entry->firstPID = PID;

	return i;
}

size_t StrategyMemoData::registerSpecies(Pokemon * pkm) {
	return registerSpecies(pkm->species, pkm->PID, pkm->SID, pkm->TID);
}

void StrategyMemoData::deleteEntry(size_t index) {
	if ((index >= 500) || (nbEntries == 0)) return;
	StrategyMemoEntry* entries2[500] = { NULL };
	StrategyMemoEntry* emptyobj = entries[index]->create();
	delete entries[index];
	std::copy(entries, entries + index, entries2);
	std::copy(entries + index + 1, entries + 500, entries2 + index);
	entries2[499] = emptyobj;

	std::copy(entries2, entries2 + 500, entries);
}

size_t StrategyMemoData::recount(void) const {
	size_t i = 0;
	while (i < 500 && getSpeciesData(entries[i]->species).isValid) ++i;
	return i;
}

void StrategyMemoData::sortedBySpeciesIndex(StrategyMemoEntry* dst[0x19b]) {
	std::fill(dst, dst + 0x19b, (StrategyMemoEntry*)NULL);
	for (size_t i = 0; i < (size_t)nbEntries; ++i) {
		size_t index = (size_t)entries[i]->species;
		if ((dst[index] != NULL) && (index <= 0x19b) && (getSpeciesData(entries[i]->species).isValid)) dst[index] = entries[i];
	}
}

void StrategyMemoData::fixInvalidEntries(void) {
	StrategyMemoEntry* bySpecies[0x19b] = { NULL };
	StrategyMemoEntry* entries2[500] = { NULL };

	StrategyMemoEntry* emptyobj = entries[0]->create();

	nbEntries = 0;
	for (size_t i = 0; i < 500; ++i) {
		size_t index = (size_t)entries[i]->species;
		if ((bySpecies[index] != NULL) && (index <= 0x19b) && (getSpeciesData(entries[i]->species).isValid)) {
			bySpecies[index] = entries[i];
			entries2[nbEntries++] = entries[i];
		}
		else {
			delete entries[i];
		}
	}

	for (size_t i = 0; i < 500; ++i) {
		if (entries2[i] == NULL) entries2[i] = emptyobj->clone();
	}

	std::copy(entries2, entries2 + nbEntries, entries);
	delete emptyobj;
}

}
}