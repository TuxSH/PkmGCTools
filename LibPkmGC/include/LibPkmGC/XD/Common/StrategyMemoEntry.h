#ifndef _LIBPKMGC_XD_STRATEGY_MEMO_ENTRY_H
#define _LIBPKMGC_XD_STRATEGY_MEMO_ENTRY_H

#include <LibPkmGC/GC/Common/StrategyMemoEntry.h>

namespace LibPkmGC {
namespace XD {


class LIBPKMGC_DECL StrategyMemoEntry :
	public GC::StrategyMemoEntry
{
public:
	static const size_t size = 12;
	~StrategyMemoEntry(void);
	StrategyMemoEntry(void);
	StrategyMemoEntry(const u8* inData);

	bool isXD(void) const;
	StrategyMemoEntry* clone(void) const;
	StrategyMemoEntry* create(void) const;

	bool isInfoPartial(void) const;
	void setInfoCompleteness(bool partial);
};

}
}

#endif