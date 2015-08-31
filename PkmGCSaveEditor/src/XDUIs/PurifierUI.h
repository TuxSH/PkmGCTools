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

#ifndef _PKMGCSAVEEDITOR_PURIFIER_UI_H
#define _PKMGCSAVEEDITOR_PURIFIER_UI_H

#include <GCUIs/PokemonDisplayWidget.h>

namespace XDUIs {

class PurificationChamberWidget : public QWidget, public IDataUI {
	Q_OBJECT
public:
	PurificationChamberWidget(LibPkmGC::XD::PurificationChamber* inChamber = NULL, size_t inChamberIndex = 0, QWidget* parent = NULL);

	LibPkmGC::XD::PurificationChamber* chamber;
	size_t chamberIndex;

	void parseData(void);
	void saveChanges(void);
	void cancelChanges(void);

protected:
	void initWidget(void);

private:
	QVBoxLayout* mainLayout;
	
	GCUIs::PokemonDisplayWidget* normalPkmFlds[3];

	GCUIs::PokemonDisplayWidget* shadowPkmFld;

};

class PurifierUI : public DataUI {
	Q_OBJECT
public:
	PurifierUI(LibPkmGC::XD::PurifierData* inPurifier = NULL, QWidget* parent = NULL, Qt::WindowFlags f = Qt::Window);

	LibPkmGC::XD::PurifierData* purifier;

	void parseData(void);
	void saveChanges(void);
	void cancelChanges(void);

protected:
	void initWidget(void);

private:
	QTabWidget* tabs;
	PurificationChamberWidget *chamberFlds[9];

};

}

#endif