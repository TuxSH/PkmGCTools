#ifndef _LIBPKMGC_COLOSSEUM_SAVE_EDITING_SAVE_SLOT_H
#define _LIBPKMGC_COLOSSEUM_SAVE_EDITING_SAVE_SLOT_H

#include <LibPkmGC/GC/SaveEditing/SaveSlot.h>
#include <LibPkmGC/Colosseum/Common/Everything.h>

namespace LibPkmGC {
namespace Colosseum {
namespace SaveEditing {

/*
	size = 0x1e000
	0x00: u32 magic
	0x04: u32 saveCount
	** Metadata / game config
	0x08: VersionInfo version
	0x0c: u32 headerChecksum
	0x10: u64/u32[2] memcardUID : memcard[0:8] xor memcard[8:16] xor memcard[16:24] iirc

	0x18: **ENCRYPTED DATA**

	0x18: u32 storyModeSaveCount // saveCount minus the number of times the rules were saved
	0x20: u32 = 0
	0x31: u8 noRumble
	0x32: u16 titleScreenLanguage;
	0x78: **END OF METADATA

	0x78: substructures. In Pokémon Colosseum, they are strictly contiguous with no trash bytes in between.

	(end)-60: **END OF ENCRYPTED DATA**

	(end)-60: u8 checksum[20]; // sha1 digest
	(end)-40: u8 randomBytes[40];
*/


class LIBPKMGC_DECL SaveSlot :
	public GC::SaveEditing::SaveSlot
{
public:
	static const size_t size = 0x1e000;
	SaveSlot(void);
	SaveSlot(const SaveSlot& other);

	SaveSlot(const u8* inData, bool isDecrypted = false);

	~SaveSlot(void);

	SaveSlot* clone(void) const;
	SaveSlot* create(void) const;

	void swap(SaveSlot& other);
	SaveSlot& operator=(SaveSlot const& other);

	void save(void);

	bool checkChecksum(bool fix = false);
	bool checkHeaderChecksum(bool fix = false);
	std::pair<bool, bool> checkBothChecksums(bool fixGlobalChecksum = false, bool fixHeaderChecksum = false);
	bool isCorrupt(void);

	void saveEncrypted(u8* outBuf);

	s32 storyModeSaveCount;
	u8 checksum[20]; // digest


protected:
	void loadData(u32 flags = 0);
	void deleteFields(void);
	void loadFields(void);
private:
	void _deleteFields_extension(void);
	SaveSlot(XD::SaveEditing::SaveSlot const&);
};

}
}
}

#endif