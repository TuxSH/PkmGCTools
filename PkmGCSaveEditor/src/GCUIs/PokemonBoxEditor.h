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

#ifndef _PKMGCSAVEEDITOR_POKEMON_BOX_EDITOR_H
#define _PKMGCSAVEEDITOR_POKEMON_BOX_EDITOR_H
#include <GCUIs/PokemonDisplayWidget.h>

namespace GCUIs {

class PokemonBoxEditor : public QWidget, public IDataUI {
	Q_OBJECT
public:
	PokemonBoxEditor(LibPkmGC::GC::PokemonBox* inBox = NULL, size_t inBoxNb = 0, QWidget* parent = NULL);
	~PokemonBoxEditor(void);

	void parseData(void);
	LibPkmGC::GC::PokemonBox* box;
	size_t boxNb;

	void saveChanges(void);
	void cancelChanges(void);
	QString currentBoxName(void) const;

signals:
	void nameChanged(size_t nb, QString const& newName);
public slots:
	void nameChangedEmitter(QString const& newName);
protected:
	void initWidget(void);
private:
	bool isXD;
	
	QVBoxLayout* mainLayout;
	QFormLayout* nameLayout;
	QLineEdit* nameFld;
	QTabWidget *tabs;
	QWidget *pages[5];
	QVBoxLayout *pageLayouts[5];
	PokemonDisplayWidget* pkmFlds[30];
};

}

#endif