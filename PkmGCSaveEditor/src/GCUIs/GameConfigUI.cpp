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

#include <GCUIs/GameConfigUI.h>
#include <QMessageBox>

using namespace LibPkmGC;
using namespace GC;
namespace GCUIs {

GameConfigUI::GameConfigUI(GameConfigData * inGameConfig, QWidget * parent, Qt::WindowFlags f) : DataUI(parent, f), gameConfig(inGameConfig) {
	init();
}

void GameConfigUI::initWidget(void) {
	versionBox = new QGroupBox(tr("Game version"));
	versionFld = new VersionInfoLayout;

	titleScreenOptionsBox = new QGroupBox(tr("Title screen options"));
	titleScreenOptionsLayout = new QFormLayout;
	noRumbleFld = new QCheckBox;
	titleScreenLanguageFld = new QComboBox;

	miscellaneousBox = new QGroupBox(tr("Miscellaneous"));
	miscellaneousLayout = new QFormLayout;
	storyModeSaveCountFld = new UnsignedSpinbox<32>;

	titleScreenLanguageFld->addItems(VersionInfoLayout::languageNames());

	versionBox->setLayout(versionFld);
	
	titleScreenOptionsLayout->addRow(tr("Rumble function disabled"), noRumbleFld);
	titleScreenOptionsLayout->addRow(tr("Language"), titleScreenLanguageFld);
	titleScreenOptionsBox->setLayout(titleScreenOptionsLayout);

	miscellaneousLayout->addRow(tr("Story mode save count"), storyModeSaveCountFld);
	miscellaneousBox->setLayout(miscellaneousLayout);

	mainLayout->addWidget(versionBox);
	mainLayout->addWidget(titleScreenOptionsBox);
	mainLayout->addWidget(miscellaneousBox);

	connect(versionFld, SIGNAL(versionChanged()), this, SLOT(versionChangeHandler()));
	DataUI::initWidget();
}

void GameConfigUI::parseData(void) {
	if (gameConfig == NULL) return;
	isXD = LIBPKMGC_IS_XD(GameConfigData, gameConfig);

	versionFld->disconnect(SIGNAL(versionChanged()), this);
	versionFld->setInfo(gameConfig->version);
	connect(versionFld, SIGNAL(versionChanged()), this, SLOT(versionChangeHandler()));

	noRumbleFld->setChecked(gameConfig->noRumble);
	titleScreenLanguageFld->setCurrentIndex((int)gameConfig->titleScreenLanguage);

	storyModeSaveCountFld->setUnsignedValue(gameConfig->storyModeSaveCount);

	versionChangeHandler();
}

void GameConfigUI::saveChanges(void) {	
	gameConfig->version = versionFld->info();
	gameConfig->noRumble = noRumbleFld->isChecked();
	gameConfig->titleScreenLanguage = (LanguageIndex)titleScreenLanguageFld->currentIndex();
	gameConfig->storyModeSaveCount = storyModeSaveCountFld->unsignedValue();
}

void GameConfigUI::versionChangeHandler(void) {
	if (versionFld->info().isIncomplete())
		QMessageBox::warning(this, tr("Warning"), tr("The version info you specified is invalid, and will make the game unplayable."));
}




}
