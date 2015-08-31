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

#ifndef _PKMGCSAVEEDITOR_PC_UI_H
#define _PKMGCSAVEEDITOR_PC_UI_H

#include <Core/ItemPocketEditor.h>
#include <GCUIs/PokemonBoxEditor.h>

namespace GCUIs {

class PCUI : public DataUI {
	Q_OBJECT
public:
	PCUI(LibPkmGC::GC::PCData* inPC = NULL, QWidget* parent = NULL, Qt::WindowFlags f = Qt::Window);

	LibPkmGC::GC::PCData* PC;

	void parseData(void);
	void saveChanges(void);
	void cancelChanges(void);
public slots:
	void boxNameChangeHandler(size_t nb, QString const& newName);
protected:
	void initWidget(void);

private:
	QTabWidget* tabs;

	QVBoxLayout*  pkmStorageTabLayout;
	QWidget* pkmStorageTab;
	QFormLayout* boxSelectorLayout;
	QComboBox* boxSelector;
	QStackedWidget* boxes;


	ItemPocketEditor* itemsTab;
};

}

#endif