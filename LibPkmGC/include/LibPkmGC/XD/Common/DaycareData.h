#ifndef _LIBPKMGC_XD_DAYCARE_DATA_H
#define _LIBPKMGC_XD_DAYCARE_DATA_H

#include <LibPkmGC/GC/Common/DaycareData.h>
#include <LibPkmGC/XD/Common/Pokemon.h>

namespace LibPkmGC {
namespace XD {

class LIBPKMGC_DECL DaycareData :
	public GC::DaycareData
{
public:
	static const size_t size = 0xcc;
	DaycareData(void);
	DaycareData(DaycareData const& other);
	DaycareData(const u8* inData);
	~DaycareData(void);

	DaycareData* clone(void) const;
	DaycareData* create(void) const;

	DaycareData(Colosseum::DaycareData const& other);
private:
	void loadFields(void);
};

}
}

#endif