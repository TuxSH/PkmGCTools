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

#include <LibPkmGC/Core/VersionInfo.h>
#include <LibPkmGC/Core/Detail/StructMacros.h>

namespace LibPkmGC {

void VersionInfo::load(u8 * data) {
	LD_FIELD_E_MAX(u8, game, 0, GameIndex, Colosseum_XD);
	LD_FIELD_E_MAX(u8, currentRegion, 1, RegionIndex, PAL);
	LD_FIELD_E_MAX(u8, originalRegion, 2, RegionIndex, PAL);
	LD_FIELD_E_MAX(u8, language, 3, LanguageIndex, Spanish);
}

void VersionInfo::load(u8 lg, u8 gm) {
	const LanguageIndex L[] = { NoLanguage, Japanese, English, French, Italian, German, NoLanguage, Spanish };
	GameIndex G[16] = { NoGame, Sapphire, Ruby, Emerald, FireRed, LeafGreen }; G[15] = Colosseum_XD;

	game = G[(gm > 15) ? 0 : gm];
	language = L[(lg > 7) ? 0 : lg];

	switch (language) {
	case Japanese: originalRegion = NTSC_J; break;
	case English: originalRegion = NTSC_U; break;
	case NoLanguage: originalRegion = NoRegion; break;
	default: originalRegion = PAL; break;
	}
	currentRegion = originalRegion;

}

void VersionInfo::save(u8& lg, u8& gm) {
	const u8 L[] = { 0, 1, 2, 5, 3, 4, 7 };
	u8 G[12] = { 0, 4, 5, 0,0,0,0,0, 1, 2, 3 }; G[11] = 15;

	game = (game > Colosseum_XD) ? NoGame : game;
	language = (language > Spanish) ? NoLanguage : language;

	gm = G[game];
	lg = L[language];
}

void VersionInfo::save(u8 * data) {
	SV_FIELD_E_MAX(u8, game, 0, GameIndex, Colosseum_XD);
	SV_FIELD_E_MAX(u8, currentRegion, 1, RegionIndex, PAL);
	SV_FIELD_E_MAX(u8, originalRegion, 2, RegionIndex, PAL);
	SV_FIELD_E_MAX(u8, language, 3, LanguageIndex, Spanish);
}

bool VersionInfo::isIncomplete(void) const {
	return (game == NoGame) || (currentRegion == NoRegion) || (originalRegion == NoRegion) || (language == NoLanguage);
}

}
