#ifndef _LIBPKMGC_COLOSSEUM_STRATEGY_MEMO_DATA_H
#define _LIBPKMGC_COLOSSEUM_STRATEGY_MEMO_DATA_H

#include <LibPkmGC/GC/Common/StrategyMemoData.h>
#include <LibPkmGC/Colosseum/Common/StrategyMemoEntry.h>

namespace LibPkmGC {
namespace Colosseum {

class LIBPKMGC_DECL StrategyMemoData :
	public GC::StrategyMemoData
{
public:
	static const size_t size = 0x1774;
	~StrategyMemoData(void);
	bool isXD(void) const;

	StrategyMemoData(void);
	StrategyMemoData(const u8* inData);
	StrategyMemoData(StrategyMemoData const& other);

	StrategyMemoData* clone(void) const;
	StrategyMemoData* create(void) const;

	void save(void);

	StrategyMemoData(XD::StrategyMemoData const& other);
protected:
	void loadFields(void);
};

}
}

#endif