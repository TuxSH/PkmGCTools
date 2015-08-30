#ifndef _LIBPKMGC_XD_SAVE_EDITING_SAVE_H
#define _LIBPKMGC_XD_SAVE_EDITING_SAVE_H

#include <LibPkmGC/GC/SaveEditing/Save.h>
#include <LibPkmGC/XD/SaveEditing/SaveSlot.h>

namespace LibPkmGC {
namespace XD {
namespace SaveEditing {

class LIBPKMGC_DECL Save :
	public GC::SaveEditing::Save
{
public:
	static const size_t size = 0x56000;
	Save(void);
	Save(Save const& other);
	Save(const u8* inData, bool hasGCIData_ = false, bool isDecrypted = false);
	//~Save(void);

	Save* clone(void) const;
	Save* create(void) const;

	void save(void);

	void saveUnshuffled(void);

protected:
	void loadFields(void);

private:
	Save(Colosseum::SaveEditing::Save const&);
};

}
}
}

#endif