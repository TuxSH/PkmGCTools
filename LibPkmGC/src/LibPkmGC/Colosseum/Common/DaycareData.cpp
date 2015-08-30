#include <LibPkmGC/Colosseum/Common/DaycareData.h>


namespace LibPkmGC {
namespace Colosseum {

DaycareData::DaycareData(void) : GC::DaycareData(0x140) {
	initWithEmptyData();
}

DaycareData::DaycareData(const u8* inData) : GC::DaycareData(0x140, inData) {
	load();
}

DaycareData::DaycareData(DaycareData const& other) : GC::DaycareData(other) {}
DaycareData::~DaycareData(void) {
}

void DaycareData::loadFields(void) {
	GC::DaycareData::loadFields();
	status = (status == NotVisited) ? NoPkmDeposited : status;
	pkm = new Pokemon(data + 8);
}

DaycareData* DaycareData::clone(void) const {
	return new DaycareData(*this);
}

DaycareData* DaycareData::create(void) const {
	return new DaycareData;
}

}
}