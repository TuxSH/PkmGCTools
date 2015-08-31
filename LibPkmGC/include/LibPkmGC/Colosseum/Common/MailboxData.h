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

#ifndef _LIBPKMGC_COLOSSEUM_MAILBOX_DATA
#define _LIBPKMGC_COLOSSEUM_MAILBOX_DATA

#include <LibPkmGC/GC/Common/MailboxData.h>

namespace LibPkmGC {
namespace Colosseum {

/*
	0x00: u16 mails[32] = mailID or 255 if empty; 0x1f: invisible mail
	0x400: u16 nbMails
	0x402: u8 ?
	0x442: u8 ?
*/

class LIBPKMGC_DECL MailboxData :
	public GC::MailboxData
{
public:
	static const size_t size = 0x448;
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
	MailboxData(XD::MailboxData const&);

};

}
}

#endif