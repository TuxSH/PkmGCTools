#ifndef _LIBPKMGC_XD_BAG_DATA_H
#define _LIBPKMGC_XD_BAG_DATA_H

#include <LibPkmGC/GC/Common/BagData.h>

namespace LibPkmGC {
namespace XD {

class LIBPKMGC_DECL BagData :
	public GC::BagData
{
public:
	static const size_t size = 0x418;
	BagData(void);
	BagData(const u8* inData);
	BagData(BagData const& other);
	~BagData();

	void swap(BagData& other);

	BagData* clone(void) const;
	BagData* create(void) const;

	void save(void);

	Item battleCDs[60];
protected:
	void loadFields(void);
private:
	BagData(Colosseum::BagData const&);

};

}
}

#endif