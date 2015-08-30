#ifndef _LIBPKMGC_GC_BAG_DATA_H
#define _LIBPKMGC_GC_BAG_DATA_H

#include <LibPkmGC/Core/ItemInfo.h>
#include <LibPkmGC/Base/DataStruct.h>

namespace LibPkmGC {

LIBPKMGC_FWD_DECL_GC_CLS(BagData)
namespace GC {

class LIBPKMGC_DECL BagData :
	public Base::DataStruct
{
public:
	BagData(size_t inSize, size_t nb_regular_items, const u8* inData = NULL);

	virtual ~BagData();

	virtual BagData* clone(void) const = 0;
	virtual BagData* create(void) const = 0;

	void swap(BagData& other);

	BagData& operator=(BagData const& other);

	virtual void save(void);

	const size_t nbRegularItems;
	Item* regularItems;
	Item keyItems[43];
	Item pokeballs[16];
	Item TMs[64];
	Item berries[46];
	Item colognes[3];

protected:
	BagData(BagData const& other);

	virtual void deleteFields(void);
	virtual void loadFields(void);
};

}
}

#endif