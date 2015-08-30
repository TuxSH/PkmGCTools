#include <Core/Globals.h>

QString currentSaveFileName;
LibPkmGC::GC::SaveEditing::Save* currentSave = NULL;
LibPkmGC::GC::SaveEditing::SaveSlot* currentSaveSlot = NULL;
bool ignoreDataCorruption = false;
QString interfaceLanguage = "";
LibPkmGC::LanguageIndex dumpedNamesLanguage = LibPkmGC::NoLanguage;
bool changesMade = false;
QString lastPkmDirectory = "";
QString lastSaveDirectory = "";


inline QMap<QString, size_t> gen_lang_map(void) {
	QMap<QString, size_t> ret;
	ret["auto"] = (size_t)LibPkmGC::NoLanguage;
	ret["ja"] = (size_t)LibPkmGC::Japanese;
	ret["en"] = (size_t)LibPkmGC::English;
	ret["de"] = (size_t)LibPkmGC::German;
	ret["fr"] = (size_t)LibPkmGC::French;
	ret["it"] = (size_t)LibPkmGC::Italian;
	ret["es"] = (size_t)LibPkmGC::Spanish;
	return ret;
}

const QMap<QString, size_t> languageCodeToIndexMap = gen_lang_map();

LibPkmGC::LanguageIndex generateDumpedNamesLanguage(void) {
	if (dumpedNamesLanguage != LibPkmGC::NoLanguage) return dumpedNamesLanguage;

	QString lg = interfaceLanguage;
	LibPkmGC::LanguageIndex ret = (LibPkmGC::LanguageIndex) languageCodeToIndexMap.value(lg, (size_t)LibPkmGC::English);
	if (ret > LibPkmGC::Spanish) ret = LibPkmGC::English;
	return ret;
}