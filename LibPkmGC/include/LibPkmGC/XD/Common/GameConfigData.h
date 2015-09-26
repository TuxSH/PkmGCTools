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

#ifndef _LIBPKMGC_XD_GAME_CONFIG_DATA_H
#define _LIBPKMGC_XD_GAME_CONFIG_DATA_H

#include <LibPkmGC/GC/Common/GameConfigData.h>

namespace LibPkmGC {
namespace XD {


/*
Game configuration substructure (off 0 (total 0xa8)) :
	0x00: VersionInfo version (game, region, language)
	0x04--0x07: padding
	0x08: u64 memcardUID (see GCSaveSlot.h)
	0x10: s32 storyModeSaveCount
	0x29: u8 noRumble
	0x2a: u16 titleScreenLanguage
	0x38: s32 headerChecksum
*/

class LIBPKMGC_DECL GameConfigData :
	public GC::GameConfigData
{
public:
	static const size_t size = 0x88;
	GameConfigData(void);
	GameConfigData(GameConfigData const& other);
	GameConfigData(const u8* inData);
	~GameConfigData(void);

	GameConfigData* clone(void) const;
	GameConfigData* create(void) const;

	void save(void);
protected:
	void loadFields(void);
private:
	GameConfigData(Colosseum::GameConfigData const& other);

};

}
}

#endif