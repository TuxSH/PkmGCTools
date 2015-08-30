#include <LibPkmGC/Colosseum/Common/PlayerData.h>

namespace LibPkmGC {
namespace Colosseum {

PlayerData::PlayerData(void) : GC::PlayerData(0xb18) {
	initWithEmptyData();
}

PlayerData::PlayerData(const u8* inData) : GC::PlayerData(0xb18, inData) {
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

	LD_FIELD_E(u8, trainerGender, 0xa80, Gender);
	if (trainerGender > Female) trainerGender = Male;

	LD_FIELD(u32, money, 0xa84);
	LD_FIELD(u32, pkCoupons, 0xa88);

	LD_SUBSTRUCTURE_ARRAY(Pokemon, party, 6, 0x30);
	LD_SUBSTRUCTURE(BagData, bag, 0x780);
}

void PlayerData::save(void) {
	GC::PlayerData::save();
	if (trainerGender > Female) trainerGender = Male;
	SV_FIELD_E(u8, trainerGender, 0xa80, Gender);
	SV_FIELD(u32, money, 0xa84);
	SV_FIELD(u32, pkCoupons, 0xa88);
	SV_FIELD(u32, pkCoupons, 0xa8c);

	SV_SUBSTRUCTURE_ARRAY(Pokemon, party, 6, 0x30);
	SV_SUBSTRUCTURE(BagData, bag, 0x780);
}

}
}