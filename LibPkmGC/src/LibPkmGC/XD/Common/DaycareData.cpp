#include <LibPkmGC/XD/Common/DaycareData.h>


namespace LibPkmGC {
namespace XD {

DaycareData::DaycareData(void) : GC::DaycareData(0xcc) {
	initWithEmptyData();
}

DaycareData::DaycareData(const u8* inData) : GC::DaycareData(0xcc, inData) {
	load();
}

DaycareData::DaycareData(DaycareData const& other) : GC::DaycareData(other) {}


DaycareData::~DaycareData(void) {
}

void DaycareData::loadFields(void) {
	GC::DaycareData::loadFields();
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