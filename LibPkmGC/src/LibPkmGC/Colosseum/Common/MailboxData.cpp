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