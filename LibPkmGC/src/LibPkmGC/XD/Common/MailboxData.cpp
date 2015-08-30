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