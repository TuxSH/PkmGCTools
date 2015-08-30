#ifndef _LIBPKMGC_COLOSSEUM_SAVE_EDITING_SAVE_H
#define _LIBPKMGC_COLOSSEUM_SAVE_EDITING_SAVE_H

#include <LibPkmGC/GC/SaveEditing/Save.h>
#include <LibPkmGC/Colosseum/SaveEditing/SaveSlot.h>

namespace LibPkmGC {
namespace Colosseum {
namespace SaveEditing {

class LIBPKMGC_DECL Save :
	public GC::SaveEditing::Save
{
public:
	static const size_t size = 0x60000;
	Save(void);
	Save(Save const& other);

	Save(const u8* inData, bool hasGCIData_ = false, bool isDecrypted = false);
	//~Save(void);

	Save* clone(void) const;
	Save* create(void) const;

	void save(void);

protected:
	void loadFields(void);

private:
	Save(XD::SaveEditing::Save const&);
};

}
}
}

#endif