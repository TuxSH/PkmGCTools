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

#ifndef _PKMGCSAVEEDITOR_GAME_CONFIG_UI_H
#define _PKMGCSAVEEDITOR_GAME_CONFIG_UI_H

#include <Core/DataUI.h>
#include <Core/UnsignedSpinbox.h>
#include <Core/VersionInfoLayout.h>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QCheckBox>

namespace GCUIs {

class GameConfigUI : public DataUI {
	Q_OBJECT
public:
	GameConfigUI(LibPkmGC::GC::GameConfigData *inGameConfig = NULL, QWidget* parent = NULL, Qt::WindowFlags f = Qt::Window);

	LibPkmGC::GC::GameConfigData* gameConfig;

	void parseData(void);

	void saveChanges(void);

public slots:
	void versionChangeHandler(void);
protected:
	void initWidget(void);

private:
	QGroupBox* versionBox;
	VersionInfoLayout* versionFld;

	QGroupBox* titleScreenOptionsBox;
	QFormLayout* titleScreenOptionsLayout;
	QCheckBox *noRumbleFld;
	QComboBox* titleScreenLanguageFld;

	QGroupBox* miscellaneousBox;
	QFormLayout* miscellaneousLayout;
	UnsignedSpinbox<32>* storyModeSaveCountFld;


};

}

#endif