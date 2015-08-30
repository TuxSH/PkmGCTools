#include <LibPkmGC/Colosseum/Common/GroupBattleRule.h>

namespace LibPkmGC {
namespace Colosseum {

GroupBattleRule::GroupBattleRule(const u8* inData) : GC::GroupBattleRule(0x54, 60, inData) {
	load();
}

GroupBattleRule::GroupBattleRule(void) : GC::GroupBattleRule(0x54, 60) {
	initWithEmptyData();
}

GroupBattleRule::GroupBattleRule(GroupBattleRule const& other) : GC::GroupBattleRule(other) {}

GroupBattleRule::~GroupBattleRule()
{
}


GroupBattleRule* GroupBattleRule::clone(void) const {
	return new GroupBattleRule(*this);
}

GroupBattleRule* GroupBattleRule::create(void) const {
	return new GroupBattleRule;
}

void GroupBattleRule::loadFields(void) {
	GC::GroupBattleRule::loadFields();
	LD_ARRAY_B(u8, bannedItems, 60, 24);
}

void GroupBattleRule::save(void) {
	GC::GroupBattleRule::save();
	SV_ARRAY_B(u8, bannedItems, 60, 24);
}

}
}