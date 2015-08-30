#include <LibPkmGC/Colosseum/Common/StrategyMemoEntry.h>

namespace LibPkmGC {
namespace Colosseum {

StrategyMemoEntry::~StrategyMemoEntry(void) {
}

StrategyMemoEntry::StrategyMemoEntry(void) : GC::StrategyMemoEntry() {
	initWithEmptyData();
}

StrategyMemoEntry::StrategyMemoEntry(const u8* inData) : GC::StrategyMemoEntry(inData) {
	load();
}

bool StrategyMemoEntry::isXD(void) const {
	return false;
}

StrategyMemoEntry* StrategyMemoEntry::clone(void) const {
	return new StrategyMemoEntry(*this);
}

StrategyMemoEntry* StrategyMemoEntry::create(void) const {
	return new StrategyMemoEntry;
}

bool StrategyMemoEntry::isInfoPartial(void) const {
	return (flags == 2);
}

void StrategyMemoEntry::setInfoCompleteness(bool partial) {
	flags = (partial) ? 2 : 0;
}


}
}
