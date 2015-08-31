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

#include <Core/VersionInfoLayout.h>
#include <QObject>
using namespace LibPkmGC;


const int gameNameToID[] = { 0, 1, 2, 8, 9, 10, 11 };
const int gameIDToName[] = { 0, 1, 2,  0,0,0,0,0, 3, 4, 5, 6 };

QStringList VersionInfoLayout::languageNames(void) {
	return QStringList() << tr("None", "Language name") << tr("Japanese") << tr("English") << tr("German") << tr("French") << tr("Italian") << tr("Spanish");
}

QStringList VersionInfoLayout::languageCodes(void) {
	return QStringList("auto") << "ja" << "en" << "de" << "fr" << "it" << "es";

}
VersionInfoLayout::VersionInfoLayout(LibPkmGC::VersionInfo const& info) : QFormLayout(){
	const QStringList gameNames = QStringList() << tr("None", "Game name") << tr("Fire Red") << tr("Leaf Green") <<
		tr("Ruby") << tr("Sapphire") << tr("Emerald") << tr("Colosseum/XD");

	const QStringList regionNames = QStringList() << tr("None", "Region name") << tr("NTSC-J") << tr("NTSC-U") << tr("PAL");

	gameFld = new QComboBox;
	currentRegionFld = new QComboBox;
	originalRegionFld = new QComboBox;
	languageFld = new QComboBox;

	gameFld->addItems(gameNames);
	currentRegionFld->addItems(regionNames);
	originalRegionFld->addItems(regionNames);
	languageFld->addItems(languageNames());


	this->addRow(tr("Game"), gameFld);
	this->addRow(tr("Current region"), currentRegionFld);
	this->addRow(tr("Original region"), originalRegionFld);
	this->addRow(tr("Language"), languageFld);

	QComboBox* flds[] = { gameFld, currentRegionFld, originalRegionFld, languageFld };
	for (size_t i = 0; i < 4; ++i) connect(flds[i], SIGNAL(currentIndexChanged(int)), this, SLOT(versionChangedEmitter()));
	setInfo(info);
}

VersionInfo VersionInfoLayout::info(void) const {
	VersionInfo ret = { (GameIndex) gameNameToID[gameFld->currentIndex()], (RegionIndex) currentRegionFld->currentIndex(), 
	(RegionIndex) originalRegionFld->currentIndex(), (LanguageIndex) languageFld->currentIndex()};

	return ret;
}

void VersionInfoLayout::setInfo(LibPkmGC::VersionInfo const & info) {
	gameFld->setCurrentIndex(gameIDToName[(size_t)info.game]);
	currentRegionFld->setCurrentIndex(info.currentRegion);
	originalRegionFld->setCurrentIndex(info.originalRegion);
	languageFld->setCurrentIndex(info.language);
}

void VersionInfoLayout::versionChangedEmitter(void) {
	emit versionChanged();
}