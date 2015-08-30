#ifndef _LIBPKMGC_XD_GROUP_BATTLE_RULE_H
#define _LIBPKMGC_XD_GROUP_BATTLE_RULE_H

#include <LibPkmGC/GC/Common/GroupBattleRule.h>
#include <LibPkmGC/GC/Common/PokemonString.h>

namespace LibPkmGC {
namespace XD {

class LIBPKMGC_DECL GroupBattleRule :
	public GC::GroupBattleRule
{
public:
	static const size_t size = 0x90;
	GroupBattleRule(const u8* inData);
	GroupBattleRule(void);
	GroupBattleRule(GroupBattleRule const& other);

	~GroupBattleRule();

	void swap(GroupBattleRule& other);
	GroupBattleRule* clone(void) const;
	GroupBattleRule* create(void) const;

	void save(void);


	bool revealDeoxysForm;
	GC::PokemonString* customName; // 25 + 1

	u16 nbPkm;
	bool isBattleOpen; // unresticted number of Pkm., max. 6.
protected:
	void loadFields(void);
	void deleteFields(void);

private:
	GroupBattleRule(Colosseum::GroupBattleRule const& other);


};

}
}

#endif