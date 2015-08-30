#ifndef _LIBPKMGC_COLOSSEUM_PC_DATA_H
#define _LIBPKMGC_COLOSSEUM_PC_DATA_H

#include <LibPkmGC/GC/Common/PCData.h>
#include <LibPkmGC/Colosseum/Common/PokemonBox.h>

namespace LibPkmGC {
namespace Colosseum {

/*
	0x00: PokemonBox boxes[8]
	0x6dec -- end(0x7198): items[235]
*/

class LIBPKMGC_DECL PCData :
	public GC::PCData
{
public:
	static const size_t size = 0x7198;
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
	PCData(XD::PCData const&);
};

}
}

#endif
