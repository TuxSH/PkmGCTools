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

#ifndef _PKMGCSAVEEDITOR_STRATEGY_MEMO_ENTRY_WIDGET_H
#define _PKMGCSAVEEDITOR_STRATEGY_MEMO_ENTRY_WIDGET_H

#include <Core/DataUI.h>
#include <Core/UnsignedSpinbox.h>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QCheckBox>
#include <QRadioButton>
#include <QComboBox>
#include <QStackedWidget>
#include <QPushButton>

namespace GCUIs {

class StrategyMemoEntryWidget : public QWidget, public IDataUI {
	Q_OBJECT
public:
	StrategyMemoEntryWidget(LibPkmGC::GC::StrategyMemoEntry* inEntry = NULL, int inEntryIndex = 0, QWidget* parent = NULL);
	~StrategyMemoEntryWidget(void);

	LibPkmGC::GC::StrategyMemoEntry *entry, *entryBackup;
	int entryIndex;

	void parseData(void);
	void saveChanges(void);

signals:
	void speciesChanged(int index, size_t nameIndex);
public slots:
	void speciesChangeHandler(int nameIndex);
	void updatePIDText(void);
	void generateShinyIDs(void);
	void truncateMemoFromHere(void);
protected:
	void initWidget(void);

private:
	bool isXD;
	QVBoxLayout *mainLayout;
	QFormLayout *mainLayout2;
	QComboBox *speciesSelector;

	QCheckBox *incompleteInfoCheckBox;

	UnsignedSpinbox<16> *firstTIDFld, *firstSIDFld;
	QVBoxLayout* PIDLayout;
	UnsignedSpinbox<32> *firstPIDFld;
	QLabel* PIDText;
	QPushButton* generateShinyIDsButton;
	QPushButton* truncateMemoFromHereButton;
};


}

#endif