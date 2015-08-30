#ifndef _LIBPKMGC_XD_PC_DATA_H
#define _LIBPKMGC_XD_PC_DATA_H

#include <LibPkmGC/GC/Common/PCData.h>
#include <LibPkmGC/XD/Common/PokemonBox.h>

namespace LibPkmGC {
namespace XD {

/*
	0x00: PokemonBox boxes[8]
	0xb860: items[235]
	0xbc0c -- end(0xbc50): unknown/unused ?
*/

class LIBPKMGC_DECL PCData :
	public GC::PCData
{
public:
	static const size_t size = 0xbc50;
	PCData(void);
	PCData(PCData const& other);
	PCData(const u8* inData);
	~PCData(void);

	PCData* clone(void) const;
	PCData* create(void) const;

	void save(void);
protected:
	void loadFields(void);
private:
	PCData(Colosseum::PCData const&);
};

}
}

#endif