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

#include <LibPkmGC/XD/Common/PurificationChamber.h>

namespace LibPkmGC {
namespace XD {

PurificationChamber::PurificationChamber(void) : Base::DataStruct(0x3d8) {
	initWithEmptyData();
}

PurificationChamber::PurificationChamber(const u8* inData) : Base::DataStruct(0x3d8, inData) {
	load();
}


void PurificationChamber::deleteFields(void) {
	for (size_t i = 0; i < 4; ++i) delete normalPkm[i];
	delete shadowPkm;
}

PurificationChamber::~PurificationChamber(void) {
	PurificationChamber::deleteFields();
}

PurificationChamber::PurificationChamber(PurificationChamber const & other) : Base::DataStruct(other) {
	CL_ARRAY(normalPkm, 4);
	CL(shadowPkm);
}

PurificationChamber & PurificationChamber::operator=(PurificationChamber const & other) {
	if (this != &other) {
		Base::DataStruct::operator=(other);
		PurificationChamber::deleteFields();
		CL_ARRAY(normalPkm, 4);
		CL(shadowPkm);
	}
	return *this;
}

void PurificationChamber::swap(PurificationChamber & other) {
	Base::DataStruct::swap(other);
	SW_ARRAY(normalPkm, 4);
	SW(shadowPkm);
}

PurificationChamber* PurificationChamber::clone(void) const {
	return new PurificationChamber(*this);
}

PurificationChamber* PurificationChamber::create(void) const {
	return new PurificationChamber;
}

void PurificationChamber::loadFields(void) {
	LD_SUBSTRUCTURE_ARRAY(Pokemon, normalPkm, 4, 0);
	LD_SUBSTRUCTURE(Pokemon, shadowPkm, 0x310);
}

void PurificationChamber::save(void) {
	SV_SUBSTRUCTURE_ARRAY(Pokemon, normalPkm, 4, 0);
	SV_SUBSTRUCTURE(Pokemon, shadowPkm, 0x310);

	std::fill(data + 0x3d5, data + 0x3d8, 0);
}

}
}