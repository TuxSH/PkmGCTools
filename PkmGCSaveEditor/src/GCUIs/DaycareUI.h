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

#ifndef _PKMGCSAVEEDITOR_DAYCARE_UI_H
#define _PKMGCSAVEEDITOR_DAYCARE_UI_H

#include <GCUIs/PokemonDisplayWidget.h>

namespace GCUIs {

class DaycareUI : public DataUI {
	Q_OBJECT
public:
	DaycareUI(LibPkmGC::GC::DaycareData* inDaycare = NULL, QWidget* parent = NULL, Qt::WindowFlags f = Qt::Window);

	LibPkmGC::GC::DaycareData* daycare;

	void parseData(void);
	void saveChanges(void);
	void cancelChanges(void);
protected:
	void initWidget(void);

private:
	QFormLayout* daycareLayout;
	
	QButtonGroup* daycareStatusButtonGroup;
	QHBoxLayout* daycareStatusButtonLayout;
	QRadioButton *notVisitedButton, *emptyButton, *pkmDepositedButton;

	UnsignedSpinbox<7>* pkmInitialLevelFld;
	UnsignedSpinbox<32>* pkmInitialPurifCtrFld;
	// Cost of daycare : 100*(1 + (currentLevel - initialLevel) + 1 + int((purifCtr - initialPurifCtr)/100)) 
	// or 100*(1 + currentLevel - initialLvl) if (purifCtr - initialPurifCtr) < 100. 0 if status != PkmDeposited
	


	PokemonDisplayWidget *pkmFld;

};

}

#endif