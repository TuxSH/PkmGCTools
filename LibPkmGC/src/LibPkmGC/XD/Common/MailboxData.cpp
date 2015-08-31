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

#include <LibPkmGC/XD/Common/MailboxData.h>

namespace LibPkmGC {
namespace XD {


MailboxData::MailboxData(void) : GC::MailboxData(0x4a, 32) {
	initWithEmptyData();
}

MailboxData::MailboxData(const u8* inData) : GC::MailboxData(0x4a, 32, inData) {
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
	mails = new u16[32];
	LD_FIELD(u16, nbMails, 0);
	LD_ARRAY(u16, mails, 32, 2);
}

void MailboxData::save(void) {
	SV_FIELD(u16, nbMails, 0);
	SV_ARRAY(u16, mails, 32, 2);
}

}
}