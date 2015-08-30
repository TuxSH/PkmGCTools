#ifndef _LIBPKMGC_PURIFIER_DATA_H
#define _LIBPKMGC_PURIFIER_DATA_H

#include <LibPkmGC/XD/Common/PurificationChamber.h>

namespace LibPkmGC {
namespace XD {

/*
	0x00--end(0x2298): PurificationChamber chambers[9]
*/

class LIBPKMGC_DECL PurifierData :
	public Base::DataStruct
{
public:
	static const size_t size = 0x2298;
	PurifierData(void);
	PurifierData(const u8* inData);

	~PurifierData(void);

	PurifierData(PurifierData const& other);
	PurifierData& operator=(PurifierData const& other);
	void swap(PurifierData& other);

	PurifierData* clone(void) const;
	PurifierData* create(void) const;

	void save(void);

	PurificationChamber* chambers[9];

private:
	void deleteFields(void);
	void loadFields(void);

};

}
}

#endif