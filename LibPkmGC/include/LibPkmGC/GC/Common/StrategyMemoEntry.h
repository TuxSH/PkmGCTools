#ifndef _LIBPKMGC_GC_STRATEGY_MEMO_ENTRY_H
#define _LIBPKMGC_GC_STRATEGY_MEMO_ENTRY_H

#include <LibPkmGC/Base/DataStruct.h>
#include <LibPkmGC/Core/PokemonInfo.h>


namespace LibPkmGC {

LIBPKMGC_FWD_DECL_GC_CLS(StrategyMemoEntry)

namespace GC {

/*
	For both Colosseum and XD:
	0x00: u16 pokemonIndex | flag (Colosseum: 0 : pokémon fully registered; 0x8000 : registered as seen; XD : 0x8000 if registered)
	0x04: u16 firstSID
	0x06: u16 firstTID
	0x08: u32 firstPID
*/

class LIBPKMGC_DECL StrategyMemoEntry :
	public Base::DataStruct
{
public:
	StrategyMemoEntry(const u8* inData = NULL);
	virtual ~StrategyMemoEntry(void);
	virtual bool isXD(void) const = 0;
	virtual void save(void);

	virtual StrategyMemoEntry* clone(void) const = 0;
	virtual StrategyMemoEntry* create(void) const = 0;

	void swap(StrategyMemoEntry& other);

	bool isEmpty(void) const;

	virtual bool isInfoPartial(void) const = 0;
	virtual void setInfoCompleteness(bool partial) = 0;

	//PokemonSpeciesStatus status; // discarded in Pokémon XD, where full information is automatically obtained
	u16 flags;
	PokemonSpeciesIndex species;
	u16 firstSID, firstTID;
	u32 firstPID;

protected:
	virtual void deleteFields(void);
	virtual void loadFields(void);
};

}
}

#endif