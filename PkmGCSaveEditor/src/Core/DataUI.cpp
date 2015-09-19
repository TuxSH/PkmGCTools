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

#include <Core/DataUI.h>

DataUI::DataUI(QWidget* parent, Qt::WindowFlags f) : QDialog(parent, f), IDataUI(),  mainLayout(new QVBoxLayout),
dialogButtonBox(new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel)) {
	this->setWindowTitle(appName);
	connect(dialogButtonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(dialogButtonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void DataUI::accept(void) {
	saveChanges();
	changesMade = true;
	QDialog::accept();
}

void DataUI::reject(void) {
	cancelChanges();
	QDialog::reject();
}

void DataUI::initWidget(void) {
	mainLayout->addWidget(dialogButtonBox);
	this->setLayout(mainLayout);
}