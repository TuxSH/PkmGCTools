#include <LibPkmGC/Colosseum/Common/BattleModeData.h>

namespace LibPkmGC {
namespace Colosseum {

BattleModeData::BattleModeData(void) : GC::BattleModeData(0xcc2c) {
	initWithEmptyData();
}

BattleModeData::BattleModeData(const u8* inData) : GC::BattleModeData(0xcc2c, inData) {
	load();
}

BattleModeData::BattleModeData(BattleModeData const& other) : GC::BattleModeData(other) {}


BattleModeData::~BattleModeData()
{
}

BattleModeData* BattleModeData::clone(void) const
{
	return new BattleModeData(*this);
}

BattleModeData* BattleModeData::create(void) const
{
	return new BattleModeData;
}

void BattleModeData::loadFields(void) {
	LD_SUBSTRUCTURE_ARRAY(GroupBattleRule, rules, 6, 0xc16c);
	//LD_FIELD_B(u8, groupBattleModeUsed, 0x360);
}

void BattleModeData::save(void) {
	SV_SUBSTRUCTURE_ARRAY(GroupBattleRule, rules, 6, 0xc16c);
	//SV_FIELD_B(u8, groupBattleModeUsed, 0x360);
}

}
}