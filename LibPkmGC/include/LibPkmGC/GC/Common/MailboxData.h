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

#ifndef _LIBPKMGC_GC_MAILBOX_DATA
#define _LIBPKMGC_GC_MAILBOX_DATA

#include <LibPkmGC/Base/DataStruct.h>

#define LIBPKMGC_MAILBOX_EMPTY_MAIL 255

namespace LibPkmGC {

LIBPKMGC_FWD_DECL_GC_CLS(MailboxData)

namespace GC {

class LIBPKMGC_DECL MailboxData :
	public Base::DataStruct
{
public:
	MailboxData(size_t inSize, u16 max_nb_mails, const u8* inData = NULL);
	virtual ~MailboxData();

	void swap(MailboxData& other);

	MailboxData& operator=(MailboxData const& other);

	virtual MailboxData* clone(void) const = 0;
	virtual MailboxData* create(void) const = 0;

	bool isMailEmpty(size_t i);

	u16 nbMails;
	u16* mails;
	const u16 maxNbMails;

protected:
	MailboxData(MailboxData const& other);

	virtual void deleteFields(void);

};

}
}

#endif