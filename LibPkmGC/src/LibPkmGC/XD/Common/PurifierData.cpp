#include <LibPkmGC/XD/Common/PurifierData.h>

namespace LibPkmGC {
namespace XD {

PurifierData::PurifierData(void) : Base::DataStruct(0x2298) {
	initWithEmptyData();
}

PurifierData::PurifierData(const u8* inData) : Base::DataStruct(0x2298, inData) {
	load();
}


void PurifierData::deleteFields(void) {
	for (size_t i = 0; i < 9; ++i) delete chambers[i];
}

PurifierData::~PurifierData(void) {
	PurifierData::deleteFields();
}

PurifierData::PurifierData(PurifierData const & other) : Base::DataStruct(other) {
	CL_ARRAY(chambers, 9);
}

PurifierData & PurifierData::operator=(PurifierData const & other){
	Base::DataStruct::operator=(other);
	if (this != &other) {
		CL_ARRAY(chambers, 9);
	}
	return *this;
}

void PurifierData::swap(PurifierData & other) {
	Base::DataStruct::swap(other);
	SW_ARRAY(chambers, 9);
}

PurifierData* PurifierData::clone(void) const {
	return new PurifierData(*this);
}

PurifierData* PurifierData::create(void) const {
	return new PurifierData;
}

void PurifierData::loadFields(void) {
	LD_SUBSTRUCTURE_ARRAY(PurificationChamber, chambers, 9, 0);
}

void PurifierData::save(void) {
	SV_SUBSTRUCTURE_ARRAY(PurificationChamber, chambers, 9, 0);
}

}
}