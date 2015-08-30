#ifndef _LIBPKMGC_GC_GROUP_BATTLE_RULE_H
#define _LIBPKMGC_GC_GROUP_BATTLE_RULE_H

#include <LibPkmGC/Base/DataStruct.h>

namespace LibPkmGC {

enum ItemRestrictionLevel {
	AllItemsAllowed = 0,
	NoItemAllowed = 1,
	SomeItemsAllowed = 2
};

LIBPKMGC_FWD_DECL_GC_CLS(GroupBattleRule)
namespace GC {

class LIBPKMGC_DECL GroupBattleRule :
	public Base::DataStruct
{
public:
	GroupBattleRule(size_t inSize, size_t nb_banned_items, const u8* inData = NULL);

	virtual ~GroupBattleRule(void);

	GroupBattleRule& operator=(GroupBattleRule const& other);
	virtual GroupBattleRule* clone(void) const = 0;
	virtual GroupBattleRule* create(void) const = 0;

	void swap(GroupBattleRule& other);
	virtual void save(void);

	u16 minLevel, maxLevel;
	u16 maxLevelSum;
	ItemRestrictionLevel itemRestrictions;
	bool noSpeciesClause, noItemClause, noSleepClause, noFreezeClause;
	bool noSkillSwap, explosionClause, noRequiemClause, allowFixedDmgAbilities;

	s16 maxBattleDuration, orderTimeout; // resp. in min., sec. if negative, it's the opposite of the suggested value

	const size_t nbBannableItems;
	bool* bannedItems; // 60 or 62

protected:
	GroupBattleRule(GroupBattleRule const& other);
	virtual void deleteFields(void);
	virtual void loadFields(void);
};

}
}

#endif