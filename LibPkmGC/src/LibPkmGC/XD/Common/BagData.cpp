#include <LibPkmGC/XD/Common/BagData.h>

namespace LibPkmGC {
namespace XD {

BagData::BagData(void) : GC::BagData(0x418, 30) {
	initWithEmptyData();
}

BagData::BagData(const u8* inData) : GC::BagData(0x418, 30, inData) {
	load();
}

BagData::BagData(BagData const& other) : GC::BagData(other) {
	CP_ARRAY(battleCDs, 60);
}


BagData::~BagData(){
}

void BagData::swap(BagData& other) {
	GC::BagData::swap(other);
	SW_ARRAY(battleCDs, 60);
}

BagData* BagData::clone(void) const {
	return new BagData(*this);
}

BagData* BagData::create(void) const {
	return new BagData;
}

void BagData::loadFields(void) {
	GC::BagData::loadFields();
	for (size_t i = 0; i < 60; ++i)
		battleCDs[i].load(data + 0x328 + 4 * i);
}

void BagData::save(void) {
	GC::BagData::save();
	for (size_t i = 0; i < 60; ++i)
		battleCDs[i].save(data + 0x328 + 4 * i);
}

}
}