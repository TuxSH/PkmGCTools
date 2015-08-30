#ifndef _PKMGCSAVEEDITOR_VERSION_INFO_LAYOUT_H
#define _PKMGCSAVEEDITOR_VERSION_INFO_LAYOUT_H

#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <LibPkmGC/Core/PokemonInfo.h>
#include <Core/IDataUI.h>


class VersionInfoLayout : public QFormLayout {
	Q_OBJECT
public:
	static QStringList languageNames(void);
	static QStringList languageCodes(void);
	//LibPkmGC::VersionInfo info;

	VersionInfoLayout(LibPkmGC::VersionInfo const& inInfo = LibPkmGC::VersionInfo());
	
	LibPkmGC::VersionInfo info(void) const;
	void setInfo(LibPkmGC::VersionInfo const& info);

signals:
	void versionChanged(void);

public slots:
	void versionChangedEmitter(void);
private:

	QComboBox *gameFld, *currentRegionFld, *originalRegionFld, *languageFld;
};

#endif