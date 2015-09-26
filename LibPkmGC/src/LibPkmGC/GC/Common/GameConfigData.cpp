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

#include <LibPkmGC/GC/Common/GameConfigData.h>

namespace LibPkmGC {
namespace GC {

GameConfigData::GameConfigData(size_t inSize, const u8* inData) : Base::DataStruct(inSize, inData) {
}

void GameConfigData::deleteFields(void) {
}

GameConfigData::~GameConfigData(void) {
	GameConfigData::deleteFields();
}

GameConfigData::GameConfigData(GameConfigData const& other) : Base::DataStruct(other){
	CP(version);
	CP(headerChecksum);
	CP_ARRAY(memcardUID, 2);
	CP(storyModeSaveCount);
	CP(titleScreenLanguage);
	CP(noRumble);
}

void GameConfigData::swap(GameConfigData& other) {
	if (fixedSize != other.fixedSize) throw std::invalid_argument("fixedSize != other->fixedSize");
	Base::DataStruct::swap(other);
	SW(version);
	SW(headerChecksum);
	SW_ARRAY(memcardUID, 2);
	SW(storyModeSaveCount);
	SW(titleScreenLanguage);
	SW(noRumble);
}

GameConfigData& GameConfigData::operator=(GameConfigData const& other) {
	if (fixedSize != other.fixedSize) throw std::invalid_argument("fixedSize != other->fixedSize");

	Base::DataStruct::operator=(other);
	if (this != &other) {
		CP(version);
		CP(headerChecksum);
		CP_ARRAY(memcardUID, 2);
		CP(storyModeSaveCount);
		CP(titleScreenLanguage);
		CP(noRumble);
	}
	return *this;
}

void GameConfigData::loadFields(void) {
	version.load(data);
	LD_ARRAY(u32, memcardUID, 2, 8);
	LD_FIELD(s32, storyModeSaveCount, 0x10);
	LD_FIELD_B(u8, noRumble, 0x29);
	LD_FIELD_E(u16, titleScreenLanguage, 0x2a, LanguageIndex);
}

void GameConfigData::save(void) {
	version.save(data);
	SV_ARRAY(u32, memcardUID, 2, 8);
	SV_FIELD(s32, storyModeSaveCount, 0x10);
	SV_FIELD_B(u8, noRumble, 0x29);
	SV_FIELD_E(u16, titleScreenLanguage, 0x2a, LanguageIndex);
}

}
}