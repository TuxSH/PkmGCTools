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