#include <LibPkmGC/Colosseum/Common/BagData.h>

namespace LibPkmGC {
namespace Colosseum {

BagData::BagData(void) : GC::BagData(0x300, 20) {
	initWithEmptyData();
}

BagData::BagData(const u8* inData) : GC::BagData(0x300, 20, inData) {
	load();
}

BagData::BagData(BagData const& other) : GC::BagData(other){}

BagData::~BagData(){
}

BagData* BagData::clone(void) const {
	return new BagData(*this);
}

BagData* BagData::create(void) const {
	return new BagData;
}

}
}