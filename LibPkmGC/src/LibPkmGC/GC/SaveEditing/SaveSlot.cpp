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

#include <LibPkmGC/GC/SaveEditing/SaveSlot.h>

namespace LibPkmGC {
namespace GC {
namespace SaveEditing {

SaveSlot::SaveSlot(size_t inSize, size_t nb_random_bytes, const u8* inData) : Base::DataStruct(inSize, inData), nbRandomBytes(nb_random_bytes) {
}

void SaveSlot::deleteFields(void) {
	delete[] randomBytes;
	delete gameConfig;
	delete player;
	delete PC;
	delete mailbox;
	delete daycare;
	delete strategyMemo;
	delete battleMode;
	delete ribbonDescriptions;
}

SaveSlot::~SaveSlot(void) {
	SaveSlot::deleteFields();
}

SaveSlot::SaveSlot(const SaveSlot& other) : Base::DataStruct(other), magic(other.magic), saveCount(other.saveCount), nbRandomBytes(other.nbRandomBytes){
	randomBytes = new u8[nbRandomBytes];
	std::copy(other.randomBytes, other.randomBytes + nbRandomBytes, randomBytes);

	CL(gameConfig);
	CL(player);
	CL(PC);
	CL(mailbox);
	CL(daycare);
	CL(strategyMemo);
	CL(battleMode);

	CL(ribbonDescriptions);
}


void SaveSlot::swap(SaveSlot& other) {
	if (nbRandomBytes != other.nbRandomBytes) throw std::invalid_argument("this->nbRandomBytes != other.nbRandomBytes");
	Base::DataStruct::swap(other);
	SW(magic);
	SW(saveCount);
	SW(gameConfig);
	SW(player);
	SW(PC);
	SW(mailbox);
	SW(daycare);
	SW(strategyMemo);
	SW(battleMode);

	SW(ribbonDescriptions);

	SW(randomBytes);
}

SaveSlot& SaveSlot::operator=(SaveSlot const& other) {
	if (nbRandomBytes != other.nbRandomBytes) throw std::invalid_argument("this->nbRandomBytes != other.nbRandomBytes");

	Base::DataStruct::operator=(other);
	if (this != &other) {
		deleteFields();
		randomBytes = new u8[nbRandomBytes];
		CP_ARRAY(randomBytes, nbRandomBytes);
		CP(magic);
		CP(saveCount);

		CL(gameConfig);
		CL(player);
		CL(PC);
		CL(mailbox);
		CL(daycare);
		CL(strategyMemo);
		CL(battleMode);

		CL(ribbonDescriptions);
	}
	return *this;
}

void SaveSlot::reload(const u8* inData, u32 flags) {
	if (inData == NULL) Base::DataStruct::reload(NULL, 1);
	else Base::DataStruct::reload(inData, flags);
}


}
}
}