#include <LibPkmGC/XD/Common/StrategyMemoEntry.h>

namespace LibPkmGC {
namespace XD {

StrategyMemoEntry::~StrategyMemoEntry(void) {
}

StrategyMemoEntry::StrategyMemoEntry(void) : GC::StrategyMemoEntry() {
	initWithEmptyData();
}

StrategyMemoEntry::StrategyMemoEntry(const u8* inData) : GC::StrategyMemoEntry(inData) {
	load();
}

bool StrategyMemoEntry::isXD(void) const {
	return true;
}

StrategyMemoEntry* StrategyMemoEntry::clone(void) const {
	return new StrategyMemoEntry(*this);
}

StrategyMemoEntry* StrategyMemoEntry::create(void) const {
	return new StrategyMemoEntry;
}

bool StrategyMemoEntry::isInfoPartial(void) const{
	return false;
}

void StrategyMemoEntry::setInfoCompleteness(bool partial){
	flags = (species == NoSpecies) ? 0 : 2;
}

}
}