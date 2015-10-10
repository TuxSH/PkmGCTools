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

#ifndef _PKMGCSAVEEDITOR_AUTOCOMPLETING_COMBO_BOX_H
#define _PKMGCSAVEEDITOR_AUTOCOMPLETING_COMBO_BOX_H

#include <QComboBox>
#include <QCompleter>

class AutocompletingComboBox : public QComboBox {
	Q_OBJECT

public:
	AutocompletingComboBox(QWidget* parent = 0);

public slots:
	void resetColor(void);

protected:
	void focusOutEvent(QFocusEvent* ev);

};

#endif