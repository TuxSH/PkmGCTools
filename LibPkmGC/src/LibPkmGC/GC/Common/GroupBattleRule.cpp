#include <LibPkmGC/GC/Common/GroupBattleRule.h>

namespace LibPkmGC {
namespace GC {

GroupBattleRule::GroupBattleRule(size_t inSize, size_t nb_bannable_items, const u8* inData) : Base::DataStruct(inSize, inData), nbBannableItems(nb_bannable_items) {
}


GroupBattleRule::GroupBattleRule(GroupBattleRule const& other) : Base::DataStruct(other), nbBannableItems(other.nbBannableItems) {
	*this = other;
}
void GroupBattleRule::deleteFields(void) {
	delete bannedItems;
}

GroupBattleRule::~GroupBattleRule(void) {
	delete bannedItems;
}

void GroupBattleRule::swap(GroupBattleRule & other) {
	if (nbBannableItems != other.nbBannableItems) throw std::invalid_argument("this->nbBannableItems != other.nbBannableItems");

	Base::DataStruct::swap(other);
	SW(minLevel);
	SW(maxLevel);
	SW(maxLevelSum);
	SW(itemRestrictions);
	SW(noSpeciesClause);
	SW(noItemClause);
	SW(noSleepClause);
	SW(noFreezeClause);
	SW(noSkillSwap);
	SW(explosionClause);
	SW(noRequiemClause);
	SW(allowFixedDmgAbilities);
	SW(maxBattleDuration);
	SW(orderTimeout);
	SW_ARRAY(bannedItems, nbBannableItems);
}

GroupBattleRule& GroupBattleRule::operator=(GroupBattleRule const& other) {
	if (nbBannableItems != other.nbBannableItems) throw std::invalid_argument("this->nbBannableItems != other.nbBannableItems");
	if (this != &other) {
		Base::DataStruct::operator=(other);
		CP(minLevel);
		CP(maxLevel);
		CP(maxLevelSum);
		CP(itemRestrictions);
		CP(noSpeciesClause);
		CP(noItemClause);
		CP(noSleepClause);
		CP(noFreezeClause);
		CP(noSkillSwap);
		CP(explosionClause);
		CP(noRequiemClause);
		CP(allowFixedDmgAbilities);
		CP(maxBattleDuration);
		CP(orderTimeout);
		CP_ARRAY(bannedItems, nbBannableItems);
	}
	return *this;
}

void GroupBattleRule::loadFields(void) {
	bannedItems = new bool[nbBannableItems];
	LD_FIELD(u16, minLevel, 0);
	LD_FIELD(u16, maxLevel, 2);
	LD_FIELD(u16, maxLevelSum, 4);
	LD_FIELD_E(u32, itemRestrictions, 8, ItemRestrictionLevel);
	LD_FIELD_B(u8, noSpeciesClause, 12);
	LD_FIELD_B(u8, noItemClause, 13);
	LD_FIELD_B(u8, noSleepClause, 14);
	LD_FIELD_B(u8, noFreezeClause, 15);
	LD_FIELD_B(u8, noSkillSwap, 16);
	LD_FIELD_B(u8, explosionClause, 17);
	LD_FIELD_B(u8, noRequiemClause, 18);
	LD_FIELD_B(u8, allowFixedDmgAbilities, 19);
	LD_FIELD(s16, maxBattleDuration, 20);
	LD_FIELD(s16, orderTimeout, 22);
}

void GroupBattleRule::save(void) {
	SV_FIELD(u16, minLevel, 0);
	SV_FIELD(u16, maxLevel, 2);
	SV_FIELD(u16, maxLevelSum, 4);
	SV_FIELD_E(u32, itemRestrictions, 8, ItemRestrictionLevel);
	SV_FIELD_B(u8, noSpeciesClause, 12);
	SV_FIELD_B(u8, noItemClause, 13);
	SV_FIELD_B(u8, noSleepClause, 14);
	SV_FIELD_B(u8, noFreezeClause, 15);
	SV_FIELD_B(u8, noSkillSwap, 16);
	SV_FIELD_B(u8, explosionClause, 17);
	SV_FIELD_B(u8, noRequiemClause, 18);
	SV_FIELD_B(u8, allowFixedDmgAbilities, 19);
	SV_FIELD(s16, maxBattleDuration, 20);
	SV_FIELD(s16, orderTimeout, 22);
}

}
}