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

#include <LibPkmGC/XD/Common/PCData.h>

namespace LibPkmGC {
namespace XD {

PCData::PCData(void) : GC::PCData(0xbc50, 8) {
	initWithEmptyData();
}

PCData::PCData(const u8* inData) : GC::PCData(0xbc50, 8, inData) {
	load();
}

PCData::PCData(PCData const& other) : GC::PCData(other) {}


PCData::~PCData(void) {
}

PCData* PCData::clone(void) const {
	return new PCData(*this);
}

PCData* PCData::create(void) const {
	return new PCData;
}



void PCData::loadFields(void) {
	boxes = new GC::PokemonBox*[nbBoxes];

	LD_SUBSTRUCTURE_ARRAY(PokemonBox, boxes, 8, 0);

	for (size_t i = 0; i < 235; ++i)
		items[i].load(data + 0xb860 + 4*i);
}

void PCData::save(void) {
	SV_SUBSTRUCTURE_ARRAY(PokemonBox, boxes, 8, 0);

	for (size_t i = 0; i < 235; ++i)
		items[i].save(data + 0xb860 + 4*i);
}

}
}