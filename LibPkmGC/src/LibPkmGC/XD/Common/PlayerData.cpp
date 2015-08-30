#include <LibPkmGC/XD/Common/PlayerData.h>

namespace LibPkmGC {
namespace XD {

PlayerData::PlayerData(void) : GC::PlayerData(0x978) {
	initWithEmptyData();
}

PlayerData::PlayerData(const u8* inData) : GC::PlayerData(0x978, inData) {
	load();
}

PlayerData::PlayerData(PlayerData const& other) : GC::PlayerData(other) {}


PlayerData::~PlayerData(void){
}

PlayerData* PlayerData::clone(void) const {
	return new PlayerData(*this);
}

PlayerData* PlayerData::create(void) const {
	return new PlayerData;
}

void PlayerData::loadFields(void) {
	GC::PlayerData::loadFields();
	LD_FIELD_E(u8, trainerGender, 0x8e0, Gender);
	if (trainerGender > Female) trainerGender = Male;

	LD_FIELD(u32, money, 0x8e4);
	LD_FIELD(u32, pkCoupons, 0x8e8);

	LD_SUBSTRUCTURE_ARRAY(Pokemon, party, 6, 0x30);
	LD_SUBSTRUCTURE(BagData, bag, 0x4c8);
}

void PlayerData::save(void) {
	GC::PlayerData::save();
	if (trainerGender > Female) trainerGender = Male;
	SV_FIELD_E(u8, trainerGender, 0x8e0, Gender);

	SV_FIELD(u32, money, 0x8e4);
	SV_FIELD(u32, pkCoupons, 0x8e8);
	SV_FIELD(u32, pkCoupons, 0x8ec);

	SV_SUBSTRUCTURE_ARRAY(Pokemon, party, 6, 0x30);
	SV_SUBSTRUCTURE(BagData, bag, 0x4c8);

}

}
}