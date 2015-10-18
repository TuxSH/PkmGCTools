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

#ifndef _LIBPKMGC_VERSION_INFO_H
#define _LIBPKMGC_VERSION_INFO_H

#include <LibPkmGC/Core/IntegerTypes.h>

namespace LibPkmGC {

enum GameIndex {
	NoGame = 0,
	BonusDisc = 0,
	FireRed = 1,
	LeafGreen = 2,

	Sapphire = 8,
	Ruby = 9,
	Emerald = 10,

	Colosseum_XD = 11
};
enum RegionIndex {
	NoRegion = 0, NTSC_J = 1, NTSC_U = 2, PAL = 3
};
enum LanguageIndex {
	NoLanguage = 0, Japanese = 1, English = 2, German = 3, French = 4, Italian = 5, Spanish = 6
};

struct LIBPKMGC_DECL VersionInfo {
	/* The following enum values come from Col/XD */

	GameIndex game;
	RegionIndex currentRegion;
	RegionIndex originalRegion;

	LanguageIndex language;

	void load(u8* data);
	void load(u8 lg, u8 gm); // GBA
	void save(u8* data);
	void save(u8& lg, u8& gm); // GBA

	bool isIncomplete(void) const;

};

const VersionInfo emptyVersionInfo = { NoGame, NoRegion, NoRegion, NoLanguage };

}

#endif