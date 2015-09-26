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

#ifndef _LIBPKMGC_GC_GAME_CONFIG_DATA_H
#define _LIBPKMGC_GC_GAME_CONFIG_DATA_H

#include <LibPkmGC/Base/DataStruct.h>
#include <LibPkmGC/Core/PokemonInfo.h>

namespace LibPkmGC {

LIBPKMGC_FWD_DECL_GC_CLS(GameConfigData)

namespace GC {


class LIBPKMGC_DECL GameConfigData :
	public Base::DataStruct
{
public:
	GameConfigData(size_t inSize, const u8* inData = NULL);
	virtual ~GameConfigData(void);

	virtual GameConfigData* clone(void) const = 0;
	virtual GameConfigData* create(void) const = 0;

	virtual void swap(GameConfigData& other);
	virtual GameConfigData& operator=(GameConfigData const& other);

	VersionInfo version;

	s32 headerChecksum; // definition and location vary across Colosseum and XD 
	u32 memcardUID[2]; // u64. memcard[0:8] xor memcard[8:16] xor memcard[16:24] iirc
	s32 storyModeSaveCount;
	LanguageIndex titleScreenLanguage;
	bool noRumble;

	virtual void save(void);
protected:
	GameConfigData(GameConfigData const& other);
	void deleteFields(void);
	virtual void loadFields(void);
};

}
}

#endif