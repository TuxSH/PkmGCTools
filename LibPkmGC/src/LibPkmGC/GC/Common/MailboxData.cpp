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

#include <LibPkmGC/GC/Common/MailboxData.h>

namespace LibPkmGC {
namespace GC {

MailboxData::MailboxData(size_t inSize, u16 max_nb_mails, const u8* inData) : Base::DataStruct(inSize, inData), maxNbMails(max_nb_mails) {
}

void MailboxData::deleteFields(void) {
	delete[] mails;
}

MailboxData::~MailboxData() {
	MailboxData::deleteFields();
}

void MailboxData::swap(MailboxData & other) {
	if (maxNbMails != other.maxNbMails) throw std::invalid_argument("maxNbMails != other.maxNbMails");
	Base::DataStruct::swap(other);
	SW(nbMails);
	SW(mails);
}

MailboxData::MailboxData(MailboxData const & other) : Base::DataStruct(other), nbMails(other.nbMails), maxNbMails(other.maxNbMails) {
	mails = new u16[nbMails];
	CP_ARRAY(mails, nbMails);
}

MailboxData & MailboxData::operator=(MailboxData const & other) {
	if (maxNbMails != other.maxNbMails) throw std::invalid_argument("maxNbMails != other.maxNbMails");

	Base::DataStruct::operator=(other);
	if (this != &other) {
		MailboxData::deleteFields();
		CP(nbMails);
		mails = new u16[nbMails];
		CP_ARRAY(mails, nbMails);
	}
	return *this;
}

bool MailboxData::isMailEmpty(size_t i) {
	return mails[i] == LIBPKMGC_MAILBOX_EMPTY_MAIL;
}

}
}