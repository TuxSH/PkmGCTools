#ifndef _LIBPKMGC_COLOSSEUM_BAG_DATA_H
#define _LIBPKMGC_COLOSSEUM_BAG_DATA_H

#include <LibPkmGC/GC/Common/BagData.h>

namespace LibPkmGC {
namespace Colosseum {

class LIBPKMGC_DECL BagData :
	public GC::BagData
{
public:
	static const size_t size = 0x300;
	BagData(void);
	BagData(BagData const& other);
	BagData(const u8* inData);
	~BagData();

	void swap(BagData& other);

	BagData* clone(void) const;
	BagData* create(void) const;


private:
	BagData(XD::BagData const&);
};

}
}

#endif