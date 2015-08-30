#include <LibPkmGC/XD/Common/BattleModeData.h>

namespace LibPkmGC {
namespace XD {

BattleModeData::BattleModeData(void) : GC::BattleModeData(0x364) {
	initWithEmptyData();
}

BattleModeData::BattleModeData(const u8* inData) : GC::BattleModeData(0x364, inData) {
	load();
}

BattleModeData::BattleModeData(BattleModeData const& other) : GC::BattleModeData(other) {}

BattleModeData::~BattleModeData()
{
}


void BattleModeData::swap(BattleModeData& other) {
	GC::BattleModeData::swap(other);
	SW(battleModeUsed);
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
	LD_SUBSTRUCTURE_ARRAY(GroupBattleRule, rules, 6, 0);
	LD_FIELD_B(u8, battleModeUsed, 0x360);
}

void BattleModeData::save(void) {
	SV_SUBSTRUCTURE_ARRAY(GroupBattleRule, rules, 6, 0);
	SV_FIELD_B(u8, battleModeUsed, 0x360);
	std::fill(data + 0x361, data + 0x363, 0);
}

}
}