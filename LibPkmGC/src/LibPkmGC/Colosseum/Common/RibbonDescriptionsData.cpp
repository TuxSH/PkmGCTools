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

#include <LibPkmGC/Colosseum/Common/RibbonDescriptionsData.h>

namespace LibPkmGC {
namespace Colosseum {

RibbonDescriptionsData::~RibbonDescriptionsData(void) {
}

RibbonDescriptionsData::RibbonDescriptionsData(void) : GC::RibbonDescriptionsData() {
	initWithEmptyData();
}

RibbonDescriptionsData::RibbonDescriptionsData(const u8* inData) : GC::RibbonDescriptionsData(inData) {
	load();
}

bool RibbonDescriptionsData::isXD(void) const {
	return false;
}

RibbonDescriptionsData* RibbonDescriptionsData::clone(void) const {
	return new RibbonDescriptionsData(*this);
}

RibbonDescriptionsData* RibbonDescriptionsData::create(void) const {
	return new RibbonDescriptionsData;
}


}
}
