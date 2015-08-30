#ifndef _LIBPKMGC_COLOSSEUM_DAYCARE_DATA_H
#define _LIBPKMGC_COLOSSEUM_DAYCARE_DATA_H

#include <LibPkmGC/GC/Common/DaycareData.h>
#include <LibPkmGC/Colosseum/Common/Pokemon.h>

namespace LibPkmGC {
namespace Colosseum {

class LIBPKMGC_DECL DaycareData :
	public GC::DaycareData
{
public:
	static const size_t size = 0x140;
	DaycareData(void);
	DaycareData(const u8* inData);
	DaycareData(DaycareData const& other);
	~DaycareData(void);

	DaycareData* clone(void) const;
	DaycareData* create(void) const;

	DaycareData(XD::DaycareData const& other);
private:
	void loadFields(void);
};

}
}

#endif