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

#ifndef _LIBPKMGC_XD_MAILBOX_DATA
#define _LIBPKMGC_XD_MAILBOX_DATA

#include <LibPkmGC/GC/Common/MailboxData.h>

namespace LibPkmGC {
namespace XD {

/*
	0x00: u16 nbMails
	0x02: u16 mails[32] = mailID or 255 if empty
	0x42 -- end (0x49): unused (?)
*/

class LIBPKMGC_DECL MailboxData :
	public GC::MailboxData
{
public:
	static const size_t size = 0x4a;
	MailboxData(void);
	MailboxData(MailboxData const& other);
	MailboxData(const u8* inData);
	~MailboxData(void);

	MailboxData* clone(void) const;
	MailboxData* create(void) const;

	void save(void);
protected:
	void loadFields(void);
private:
	MailboxData(Colosseum::MailboxData const&);

};

}
}

#endif