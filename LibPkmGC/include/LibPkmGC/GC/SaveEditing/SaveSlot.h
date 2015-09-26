/*
* Copyright (C) TuxSH 2015
* This file is part of LibPkmGC.
*
* LibPkmGC is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* LibPkmGC is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with LibPkmGC.  If not, see <http://www.gnu.org/licenses/>.
*/

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


	SaveMagic magic;
	s32 saveCount;

	const size_t nbRandomBytes;
	u8* randomBytes;

	GameConfigData* gameConfig;
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