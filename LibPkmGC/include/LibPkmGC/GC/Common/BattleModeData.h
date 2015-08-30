#ifndef _LIBPKMGC_GC_BATTLE_MODE_DATA_H
#define _LIBPKMGC_GC_BATTLE_MODE_DATA_H

#include <LibPkmGC/GC/Common/GroupBattleRule.h>

namespace LibPkmGC {

LIBPKMGC_FWD_DECL_GC_CLS(BattleModeData)

namespace GC {

class LIBPKMGC_DECL BattleModeData :
	public Base::DataStruct
{
public:
	BattleModeData(size_t inSize, const u8* inData = NULL);

	virtual ~BattleModeData();

	virtual BattleModeData* clone(void) const = 0;
	virtual BattleModeData* create(void) const = 0;

	void swap(BattleModeData& other);
	BattleModeData& operator=(BattleModeData const& other);

	GroupBattleRule* rules[6];

protected:
	BattleModeData(BattleModeData const& other);

	virtual void deleteFields(void);

};

}
}

#endif