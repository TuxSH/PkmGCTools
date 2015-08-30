#ifndef _LIBPKMGC_COLOSSEUM_GROUP_BATTLE_RULE_H
#define _LIBPKMGC_COLOSSEUM_GROUP_BATTLE_RULE_H

#include <LibPkmGC/GC/Common/GroupBattleRule.h>

namespace LibPkmGC {
namespace Colosseum {

class LIBPKMGC_DECL GroupBattleRule :
	public GC::GroupBattleRule
{
public:
	static const size_t size = 0x54;
	GroupBattleRule(const u8* inData);
	GroupBattleRule(GroupBattleRule const& other);
	GroupBattleRule(void);
	~GroupBattleRule();

//	void swap(GroupBattleRule& other);
	GroupBattleRule* clone(void) const;
	GroupBattleRule* create(void) const;

	void save(void);

protected:
	void loadFields(void);

private:
	GroupBattleRule(XD::GroupBattleRule const& other);

};

}
}

#endif