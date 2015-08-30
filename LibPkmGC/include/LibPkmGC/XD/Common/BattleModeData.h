#ifndef _LIBPKMGC_XD_BATTLE_MODE_DATA_H
#define _LIBPKMGC_XD_BATTLE_MODE_DATA_H

#include <LibPkmGC/GC/Common/BattleModeData.h>
#include <LibPkmGC/XD/Common/GroupBattleRule.h>

namespace LibPkmGC {
namespace XD {

/*
	0x00: XDBattleRule rules[6]
	0x360: u8 groupBattleModeUsed
	0x361--0x363: unused/trash data
*/
class LIBPKMGC_DECL BattleModeData :
	public GC::BattleModeData
{
public:
	static const size_t size = 0x364;
	BattleModeData(void);
	BattleModeData(BattleModeData const&);
	BattleModeData(const u8* inData);
	~BattleModeData();

	void swap(BattleModeData& other);
	BattleModeData* clone(void) const;
	BattleModeData* create(void) const;

	void save(void);


	bool battleModeUsed;

private:
	void loadFields(void);
	BattleModeData(Colosseum::BattleModeData const& other);

};

}
}

#endif