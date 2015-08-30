#include <LibPkmGC/GC/Common/BattleModeData.h>

namespace LibPkmGC {
namespace GC {

BattleModeData::BattleModeData(size_t inSize, const u8* inData) : Base::DataStruct(inSize, inData) {
}

void BattleModeData::deleteFields(void) {
	for (size_t i = 0; i < 6; ++i) delete rules[i];
}

BattleModeData::~BattleModeData() {
	BattleModeData::deleteFields();
}

void BattleModeData::swap(BattleModeData& other) {
	Base::DataStruct::swap(other);
	for (size_t i = 0; i < 6; ++i) other.rules[i]->swap(*rules[i]);
}

BattleModeData::BattleModeData(BattleModeData const& other) : Base::DataStruct(other){
	CL_ARRAY(rules, 6);
}

BattleModeData & BattleModeData::operator=(BattleModeData const& other) {
	Base::DataStruct::operator=(other);
	if (this != &other) {
		CL_ARRAY(rules, 6);
	}
	return *this;
}

}
}