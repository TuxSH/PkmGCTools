#ifndef _PKMGCSAVEEDITOR_GLOBALS_H
#define _PKMGCSAVEEDITOR_GLOBALS_H

#define PKMGCSAVEEDITOR_VERSION 1000000
#define PKMGCSAVEEDITOR_VERSION_MAJOR ((PKMGCSAVEEDITOR_VERSION / 1000000) % 1000)
#define PKMGCSAVEEDITOR_VERSION_MINOR ((PKMGCSAVEEDITOR_VERSION / 1000) % 1000)
#define PKMGCSAVEEDITOR_VERSION_BUILD (PKMGCSAVEEDITOR_VERSION % 1000)

#include <boost/config/warning_disable.hpp>
#include <LibPkmGC/XD/SaveEditing/Save.h>
#include <LibPkmGC/Colosseum/SaveEditing/Save.h>
#include <LibPkmGC/Core/Localization.h>
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