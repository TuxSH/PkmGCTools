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

#include <LibPkmGC/GC/Common/BagData.h>

namespace LibPkmGC {
namespace GC {

BagData::BagData(size_t inSize, size_t nb_regular_items, const u8* inData) : Base::DataStruct(inSize, inData), nbRegularItems(nb_regular_items){
}

void BagData::deleteFields(void) {
	delete[] regularItems;
}

BagData::~BagData() {
	BagData::deleteFields();
}

void BagData::swap(BagData& other) {
	if (nbRegularItems != other.nbRegularItems) throw(std::invalid_argument("this->nbRegularItems != other.nbRegularItems"));
	Base::DataStruct::swap(other);
	SW(regularItems);
	SW_ARRAY(keyItems, 43);
	SW_ARRAY(TMs, 64);
	SW_ARRAY(berries, 46);
	SW_ARRAY(colognes, 3);
}

BagData::BagData(BagData const & other) : Base::DataStruct(other), nbRegularItems(other.nbRegularItems) {
	regularItems = new Item[nbRegularItems];
	CP_ARRAY(regularItems, nbRegularItems);
	CP_ARRAY(keyItems, 43);
	CP_ARRAY(TMs, 64);
	CP_ARRAY(berries, 46);
	CP_ARRAY(colognes, 3);
}

BagData& BagData::operator=(BagData const & other) {
	Base::DataStruct::operator=(other);
	if (nbRegularItems != other.nbRegularItems) throw(std::invalid_argument("this->nbRegularItems != other.nbRegularItems"));
	if (this != &other) {
		BagData::deleteFields();
		regularItems = new Item[nbRegularItems];
		CP_ARRAY(regularItems, nbRegularItems);
		CP_ARRAY(keyItems, 43);
		CP_ARRAY(TMs, 64);
		CP_ARRAY(berries, 46);
		CP_ARRAY(colognes, 3);
	}
	return *this;
}

void BagData::loadFields(void) {
	size_t offset = 0;
	regularItems = new Item[nbRegularItems];
#define LD_ITEMS(field, nb) for (size_t i = 0; i < nb; ++i)\
								field[i].load(data + offset + 4*i);\
							offset += 4 * nb;

	LD_ITEMS(regularItems, nbRegularItems);
	LD_ITEMS(keyItems, 43);
	LD_ITEMS(pokeballs, 16);
	LD_ITEMS(TMs, 64);
	LD_ITEMS(berries, 46);
	LD_ITEMS(colognes, 3);
}

void BagData::save(void) {
	size_t offset = 0;
#define SV_ITEMS(field, nb) for (size_t i = 0; i < nb; ++i)\
								field[i].save(data + offset + 4*i);\
							offset += 4 * nb;

	SV_ITEMS(regularItems, nbRegularItems);
	SV_ITEMS(keyItems, 43);
	SV_ITEMS(pokeballs, 16);
	SV_ITEMS(TMs, 64);
	SV_ITEMS(berries, 46);
	SV_ITEMS(colognes, 3);
}

}
}