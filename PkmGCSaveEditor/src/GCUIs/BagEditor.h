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

#ifndef _PKMGCSAVEEDITOR_BAG_EDITOR_H
#define _PKMGCSAVEEDITOR_BAG_EDITOR_H

#include <Core/ItemPocketEditor.h>
#include <LibPkmGC/GC/Common/BagData.h>
#include <LibPkmGC/XD/Common/BagData.h>
#include <QTabWidget>

namespace GCUIs {

class BagEditor : public QWidget, public IDataUI {
	Q_OBJECT
public:
	BagEditor(LibPkmGC::GC::BagData* inBag = NULL, QWidget* parent = NULL);
	~BagEditor(void);
	void parseData(void);
	LibPkmGC::GC::BagData* bag;

	void saveChanges(void);

protected:
	void initWidget(void);

private:
	bool isXD;
	QVBoxLayout* mainLayout;
	QTabWidget* tabs;
	ItemPocketEditor *regularItemsPocket, *keyItemsPocket, *pokeballsPocket, *TMsPocket, *berriesPocket, *colognesPocket, *battleCDsPocket;
};

}

#endif