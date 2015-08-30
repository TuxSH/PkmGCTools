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