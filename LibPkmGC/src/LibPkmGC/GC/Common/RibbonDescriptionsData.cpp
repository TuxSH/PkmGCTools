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

#include <LibPkmGC/GC/Common/RibbonDescriptionsData.h>

namespace LibPkmGC {
namespace GC {

RibbonDescriptionsData::RibbonDescriptionsData(const u8* inData) : Base::DataStruct(0xb, inData) {
}

void RibbonDescriptionsData::deleteFields(void) {
}


RibbonDescriptionsData::~RibbonDescriptionsData(void) {
	RibbonDescriptionsData::deleteFields();
}

void RibbonDescriptionsData::swap(RibbonDescriptionsData& other) {
	Base::DataStruct::swap(other);
	SW_ARRAY(descriptions, 11);
}

void RibbonDescriptionsData::loadFields(void) {
	LD_ARRAY_MAX(u8, descriptions, 11, 0, 65);
}

void RibbonDescriptionsData::save(void) {
	SV_ARRAY_MAX(u8, descriptions, 11, 0, 65);
}

}
}