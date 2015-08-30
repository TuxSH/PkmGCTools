#ifndef _LIBPKMGC_GC_PC_DATA_H
#define _LIBPKMGC_GC_PC_DATA_H

#include <LibPkmGC/GC/Common/PokemonBox.h>

namespace LibPkmGC {

LIBPKMGC_FWD_DECL_GC_CLS(PCData)
namespace GC {

class LIBPKMGC_DECL PCData :
	public Base::DataStruct
{
public:
	PCData(size_t inSize, size_t nb_boxes, const u8* inData = NULL);
	virtual ~PCData(void);

	virtual PCData* clone(void) const = 0;
	virtual PCData* create(void) const = 0;

	void swap(PCData& other);

	PCData& operator=(PCData const& other);

	PokemonBox** boxes;
	const size_t nbBoxes;

	Item items[235];

protected:
	PCData(PCData const& other);

	virtual void deleteFields(void);

};

}
}

#endif