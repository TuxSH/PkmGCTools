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

#include <LibPkmGC/Colosseum/Common/MailboxData.h>

namespace LibPkmGC {
namespace Colosseum {


MailboxData::MailboxData(void) : GC::MailboxData(0x448, 512) {
	initWithEmptyData();
}

MailboxData::MailboxData(const u8* inData) : GC::MailboxData(0x448, 512, inData) {
	load();
}

MailboxData::MailboxData(MailboxData const& other) : GC::MailboxData(other) {}

MailboxData::~MailboxData() {
}

MailboxData* MailboxData::clone(void) const {
	return new MailboxData(*this);
}

MailboxData* MailboxData::create(void) const {
	return new MailboxData;
}

void MailboxData::loadFields(void) {
	mails = new u16[512];
	LD_ARRAY(u16, mails, 512, 0);
	LD_FIELD(u16, nbMails, 0x400);
}

void MailboxData::save(void) {
	SV_ARRAY(u16, mails, 512, 0);
	SV_FIELD(u16, nbMails, 0x400);
}

}
}