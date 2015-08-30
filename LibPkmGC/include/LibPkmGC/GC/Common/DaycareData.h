#ifndef _LIBPKMGC_GC_DAYCARE_DATA_H
#define _LIBPKMGC_GC_DAYCARE_DATA_H

#include <LibPkmGC/GC/Common/Pokemon.h>


namespace LibPkmGC {

enum DaycareStatus {
	NotVisited = -1, NoPkmDeposited = 0, PkmDeposited = 1
};

LIBPKMGC_FWD_DECL_GC_CLS(DaycareData)

namespace GC {

/*
For both Colosseum and XD:
	0x00: s8 daycareStatus (0: no pkm, >1: pkm in daycare, <0: first visit (XD only)
	0x01: u8 initialPkmLevel;
	0x02: padding/trash data
	0x04: u32 initialPurificationCounter
	0x08--end: stored pkm
*/

// Cost of daycare : 100*(1 + (currentLevel - initialLevel) + 1 + int((purifCtr - initialPurifCtr)/100)) 
// or 100*(1 + currentLevel - initialLvl) if (purifCtr - initialPurifCtr) < 100. 0 if status != PkmDeposited
class LIBPKMGC_DECL DaycareData :
	public Base::DataStruct
{
public:
	DaycareData(size_t inSize, const u8* inData = NULL);
	virtual ~DaycareData(void);

	virtual DaycareData* clone(void) const = 0;
	virtual DaycareData* create(void) const = 0;

	virtual void swap(DaycareData& other);
	virtual DaycareData& operator=(DaycareData const& other);

	virtual void save(void);

	DaycareStatus status;
	u8 initialPkmLevel;
	u32 initialPkmPurifCounter;
	Pokemon* pkm;

protected:
	DaycareData(DaycareData const& other);

	virtual void deleteFields(void);
	virtual void loadFields(void);
};

}
}

#endif