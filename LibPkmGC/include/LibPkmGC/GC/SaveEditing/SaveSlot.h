#ifndef _LIBPKMGC_GC_SAVE_EDITING_SAVE_SLOT_H
#define _LIBPKMGC_GC_SAVE_EDITING_SAVE_SLOT_H

#include <LibPkmGC/GC/Common/Everything.h>
#include <utility>

namespace LibPkmGC {

enum SaveMagic {
	ColosseumMagic = 0x01010000,
	XDMagic = 0x01010100
};

namespace XD { namespace SaveEditing { class SaveSlot; } }
namespace Colosseum { namespace SaveEditing { class SaveSlot; } }

namespace GC {
namespace SaveEditing {


class LIBPKMGC_DECL SaveSlot : public Base::DataStruct
{
public:

	SaveSlot(size_t inSize, size_t nb_random_bytes, const u8* inData = NULL);
	SaveSlot(const SaveSlot& other);
	virtual ~SaveSlot(void);


	void swap(SaveSlot& other);
	
	SaveSlot& operator=(SaveSlot const& other);

	virtual SaveSlot* clone(void) const = 0;
	virtual SaveSlot* create(void) const = 0;

	virtual void reload(const u8* inData = NULL, u32 flags = 0);

	virtual bool checkChecksum(bool fix = false) = 0;
	virtual bool checkHeaderChecksum(bool fix = false) = 0;

	virtual std::pair<bool, bool> checkBothChecksums(bool fixGlobalChecksum = false, bool fixHeaderChecksum = false) = 0;

	virtual bool isCorrupt(void) = 0;
	virtual void saveEncrypted(u8* outBuf) = 0;


	SaveMagic magic; // 0x00 -- 0x04 (0x03 actually)
	s32 headerChecksum; // definition and location vary across Colosseum and XD 

	s32 saveCount;//, totalSaveCount;

	/* A bit inconsistent across versions */
	u32 memcardUID[2]; // u64. memcard[0:8] xor memcard[8:16] xor memcard[16:24] iirc
	VersionInfo version;
	LanguageIndex titleScreenLanguage;
	bool noRumble;

	const size_t nbRandomBytes;
	u8* randomBytes;

	PlayerData* player;
	PCData* PC;
	MailboxData* mailbox;
	DaycareData* daycare;
	StrategyMemoData* strategyMemo;
	BattleModeData* battleMode;

protected:
	virtual void deleteFields(void);

};

}
}
}

#endif