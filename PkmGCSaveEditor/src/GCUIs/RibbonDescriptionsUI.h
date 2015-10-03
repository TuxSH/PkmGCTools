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

#ifndef _PKMGCSAVEEDITOR_RIBBON_DESCRIPTIONS_UI_H
#define _PKMGCSAVEEDITOR_RIBBON_DESCRIPTIONS_UI_H

#include <GCUIs/PokemonUI.h>



namespace GCUIs {

class RibbonDescriptionsUI : public DataUI {
	Q_OBJECT
public:
	RibbonDescriptionsUI(LibPkmGC::GC::RibbonDescriptionsData* inRibbonDescriptions = NULL, QWidget *parent = NULL, Qt::WindowFlags f = Qt::Window);
	void parseData(void);
	void saveChanges(void);


	LibPkmGC::GC::RibbonDescriptionsData* ribbonDescriptions;

protected:
	void initWidget(void);
private:
	QFormLayout* descriptionsLayout;

	QComboBox* descriptionsFld[11];
	
};

}

#endif