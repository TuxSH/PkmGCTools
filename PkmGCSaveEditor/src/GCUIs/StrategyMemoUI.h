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

#ifndef _PKMGCSAVEEDITOR_STRATEGY_MEMO_UI_H
#define _PKMGCSAVEEDITOR_STRATEGY_MEMO_UI_H

#include <GCUIs/StrategyMemoEntryWidget.h>

namespace GCUIs {

class StrategyMemoUI : public DataUI {
	Q_OBJECT
public:
	StrategyMemoUI(LibPkmGC::GC::StrategyMemoData* inStrategyMemo = NULL, QWidget* parent = NULL, Qt::WindowFlags f = Qt::Window);
	~StrategyMemoUI(void);

	LibPkmGC::GC::StrategyMemoData* strategyMemo;
	LibPkmGC::GC::StrategyMemoData* strategyMemoBackup;
	
	void parseData(void);
	void saveChanges(void);
	void cancelChanges(void);
public slots:
	void updateEntryNameAndNbEntries(int index, size_t nameIndex);
	void setCurrentEntry(int index);
protected:
	void initWidget(void);
private:
	void updateEntryName(int index, size_t nameIndex);
	QFormLayout *entrySelectorLayout;
	UnsignedSpinbox<16>* nbEntriesFld;
	QComboBox *entrySelector;

	StrategyMemoEntryWidget* currentEntry; // we cannot use a QStackedWidget here
};

}

#endif