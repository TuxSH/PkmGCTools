/*
* Copyright (C) TuxSH 2015
* This file is part of PkmGCSaveEditor.
*
* PkmGCSaveEditor is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* PkmGCSaveEditor is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with PkmGCSaveEditor.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _PKMGCSAVEEDITOR_GLOBALS_H
#define _PKMGCSAVEEDITOR_GLOBALS_H

#define PKMGCSAVEEDITOR_VERSION 1001000
#define PKMGCSAVEEDITOR_VERSION_MAJOR ((PKMGCSAVEEDITOR_VERSION / 1000000) % 1000)
#define PKMGCSAVEEDITOR_VERSION_MINOR ((PKMGCSAVEEDITOR_VERSION / 1000) % 1000)
#define PKMGCSAVEEDITOR_VERSION_BUILD (PKMGCSAVEEDITOR_VERSION % 1000)

#include <boost/config/warning_disable.hpp>
#include <LibPkmGC/XD/SaveEditing/Save.h>
#include <LibPkmGC/Colosseum/SaveEditing/Save.h>
#include <LibPkmGC/Core/Localization.h>
#include <LibPkmGC/GBA/Pokemon.h>
#include <QLocale>
#include <QMap>

extern const QMap<QString, size_t> languageCodeToIndexMap;

extern QString currentSaveFileName;
extern LibPkmGC::GC::SaveEditing::Save* currentSave;
extern LibPkmGC::GC::SaveEditing::SaveSlot* currentSaveSlot;
extern bool ignoreDataCorruption;
extern QString interfaceLanguage;
extern LibPkmGC::LanguageIndex dumpedNamesLanguage;
extern bool changesMade;
extern QString lastPkmDirectory;
extern QString lastSaveDirectory;

LibPkmGC::LanguageIndex generateDumpedNamesLanguage(void);

#endif