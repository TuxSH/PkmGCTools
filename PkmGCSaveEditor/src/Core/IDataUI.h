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

#ifndef _PKMGCSAVEEDITOR_I_DATA_UI_H
#define _PKMGCSAVEEDITOR_I_DATA_UI_H

#include <LibPkmGC/Base/DataStruct.h>
#include <QObject>

class IDataUI {
public:
	virtual void parseData(void) = 0;
	virtual void saveChanges(void) = 0;
	virtual void cancelChanges(void) {}
protected:

	virtual void init(void) {
		initWidget();
		parseData();
	}
	virtual void initWidget(void) = 0;
};

#endif