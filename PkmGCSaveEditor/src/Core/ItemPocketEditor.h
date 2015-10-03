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

#ifndef _PKMGCSAVEEDITOR_ITEM_POCKET_EDITOR_H
#define _PKMGCSAVEEDITOR_ITEM_POCKET_EDITOR_H

#include <Core/ItemComboBox.h>
#include <Core/UnsignedSpinbox.h>
#include <QHBoxLayout>

#include <QVBoxLayout>
#include <Core/IDataUI.h>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QComboBox>
#include <QShortcut>

class ItemPocketEditor : public QWidget, public IDataUI {
	Q_OBJECT
public:
	ItemPocketEditor(LibPkmGC::Item* inPocket = NULL, size_t inPocketMaxSize = 0, unsigned int inFlags = 0, bool inIsXD = false, QWidget* parent = NULL);
	~ItemPocketEditor(void);

	LibPkmGC::Item* pocket;
	size_t pocketMaxSize;
	unsigned int flags;
	bool isXD;

	void parseData(void);
	void saveChanges(void);

	LibPkmGC::Item editedItem(void) const;
	void setEditedItem(LibPkmGC::Item const& val);
public slots:
	void updateMaxQuantity(void);
	void displayItem(void);
	void modifySelected(void);
	void deleteSelected(void);
protected:
	void initWidget(void);
private:
	void setItemAt(int i);
	LibPkmGC::Item *items;
	QVBoxLayout* mainLayout;
	QTableWidget* tbl;

	QHBoxLayout* actionLayout;
	ItemComboBox *itemNameFld;
	UnsignedSpinbox<16> *quantityFld;
	QPushButton *modifyButton, *deleteButton;
};

#endif