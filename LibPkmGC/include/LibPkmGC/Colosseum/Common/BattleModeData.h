#ifndef _LIBPKMGC_COLOSSEUM_BATTLE_MODE_DATA_H
#define _LIBPKMGC_COLOSSEUM_BATTLE_MODE_DATA_H

#include <LibPkmGC/GC/Common/BattleModeData.h>
#include <LibPkmGC/Colosseum/Common/GroupBattleRule.h>


namespace LibPkmGC {
namespace Colosseum {

/*
	??
	0xc16c: Colosseum::GroupBattleRules rules[26]
	??
*/
class LIBPKMGC_DECL BattleModeData :
	public GC::BattleModeData
{
public:
	static const size_t size = 0xcc2c;
	BattleModeData(void);
	BattleModeData(BattleModeData const& other);
	BattleModeData(const u8* inData);
	~BattleModeData();

	BattleModeData* clone(void) const;
	BattleModeData* create(void) const;

	void save(void);
protected:
	void loadFields(void);

private:
	BattleModeData(XD::BattleModeData const& other);

};

}
}

#endif