#include <LibPkmGC/XD/Common/StrategyMemoData.h>

namespace LibPkmGC {
namespace XD {

StrategyMemoData::StrategyMemoData(void) : GC::StrategyMemoData(0x1774) {
	initWithEmptyData();
}

StrategyMemoData::StrategyMemoData(const u8* inData) : GC::StrategyMemoData(0x1774, inData) {
	load();
}

StrategyMemoData::StrategyMemoData(StrategyMemoData const& other) : GC::StrategyMemoData(other) {}


bool StrategyMemoData::isXD(void) const {
	return true;
}

StrategyMemoData* StrategyMemoData::clone(void) const
{
	return new StrategyMemoData(*this);
}

StrategyMemoData* StrategyMemoData::create(void) const
{
	return new StrategyMemoData;
}

void StrategyMemoData::loadFields(void) {
	GC::StrategyMemoData::loadFields();
	LD_SUBSTRUCTURE_ARRAY(StrategyMemoEntry, entries, 500, 4);
}

void StrategyMemoData::save(void) {
	GC::StrategyMemoData::save();
	SV_SUBSTRUCTURE_ARRAY(StrategyMemoEntry, entries, 500, 4);

}


StrategyMemoData::~StrategyMemoData(void)
{
}

}
}