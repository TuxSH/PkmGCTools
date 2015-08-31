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

#pragma once
#ifndef _PKMGCSAVEEDITOR_DATA_UI_H
#define _PKMGCSAVEEDITOR_DATA_UI_H

#include <Core/Globals.h>
#include <Core/IDataUI.h>
#include <QDialog>
#include <QVBoxLayout>
#include <QDialogButtonBox>

class DataUI : public QDialog, public IDataUI {
	Q_OBJECT

public:
	DataUI(QWidget* parent = NULL, Qt::WindowFlags f = Qt::Window);

public slots:
	void accept(void);
	void reject(void);
protected:
	bool isXD;

	void initWidget(void);

	QVBoxLayout *mainLayout;
	QDialogButtonBox *dialogButtonBox;
};

#endif