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

#include <Core/AutocompletingComboBox.h>
#include <QAbstractItemModel>
#include <QApplication>

AutocompletingComboBox::AutocompletingComboBox(QWidget* parent) : QComboBox(parent) {
	setEditable(true);
	setInsertPolicy(QComboBox::NoInsert);
	completer()->setCompletionMode(QCompleter::PopupCompletion);

	connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(resetColor()));
}

void AutocompletingComboBox::resetColor(void) {
	QAbstractItemModel* m = completer()->model();
	if (QPalette::Base, (m->match(m->index(0, 0), Qt::DisplayRole, currentText(), 1, Qt::MatchFlags(Qt::MatchExactly | Qt::MatchWrap) ).isEmpty())) {
		QPalette pal = palette();
		pal.setColor(QPalette::Base, QColor(233,150,122));
		setPalette(pal);
	}
	else
		setPalette(QApplication::palette(this));
}

void AutocompletingComboBox::focusOutEvent(QFocusEvent * ev) {
	resetColor();
	QComboBox::focusOutEvent(ev);
}
