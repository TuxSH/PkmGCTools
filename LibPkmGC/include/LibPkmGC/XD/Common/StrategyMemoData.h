#ifndef _LIBPKMGC_XD_STRATEGY_MEMO_DATA_H
#define _LIBPKMGC_XD_STRATEGY_MEMO_DATA_H

#include <LibPkmGC/GC/Common/StrategyMemoData.h>
#include <LibPkmGC/XD/Common/StrategyMemoEntry.h>

namespace LibPkmGC {
namespace XD {

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

	StrategyMemoData(Colosseum::StrategyMemoData const& other);

protected:
	void loadFields(void);
};

}
}

#endif