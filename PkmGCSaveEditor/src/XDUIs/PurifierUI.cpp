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

#include <XDUIs/PurifierUI.h>

using namespace LibPkmGC;

namespace XDUIs {

PurificationChamberWidget::PurificationChamberWidget(XD::PurificationChamber* inChamber, size_t inChamberIndex, QWidget* parent) : QWidget(parent), 
chamber(inChamber), chamberIndex(inChamberIndex) {
	init();
}

void PurificationChamberWidget::initWidget(void) {
	mainLayout = new QVBoxLayout;

	for (size_t i = 0; i < 3; ++i) {
		normalPkmFlds[i] = new GCUIs::PokemonDisplayWidget;
		mainLayout->addWidget(normalPkmFlds[i]);
	}
	mainLayout->addStretch();
	shadowPkmFld = new GCUIs::PokemonDisplayWidget;
	mainLayout->addWidget(shadowPkmFld);
	this->setLayout(mainLayout);
}

void PurificationChamberWidget::parseData(void) {
	if (chamber == NULL) return;
	
	PokemonStorageInfo loc = { StoredInPurifier, chamberIndex, 0 };

	shadowPkmFld->pkm = chamber->shadowPkm;
	shadowPkmFld->location = loc;
	shadowPkmFld->parseData();
	for (size_t i = 0; i < 3; ++i) {
		++(loc.subIndex);
		normalPkmFlds[i]->pkm = chamber->normalPkm[i];
		normalPkmFlds[i]->location = loc;
		normalPkmFlds[i]->parseData();
	}
}

void PurificationChamberWidget::saveChanges(void) {
	for (size_t i = 0; i < 3; ++i) normalPkmFlds[i]->saveChanges();
	shadowPkmFld->saveChanges();
}

void PurificationChamberWidget::cancelChanges(void) {
	for (size_t i = 0; i < 3; ++i) normalPkmFlds[i]->cancelChanges();
	shadowPkmFld->cancelChanges();
}


PurifierUI::PurifierUI(XD::PurifierData* inPurifier, QWidget* parent, Qt::WindowFlags f) : DataUI(parent, f), purifier(inPurifier) {
	init();
}

void PurifierUI::initWidget(void) {
	tabs = new QTabWidget;
	for (size_t i = 0; i < 9; ++i) {
		chamberFlds[i] = new PurificationChamberWidget(NULL, i);
		tabs->addTab(chamberFlds[i], tr("Chamber %n", "Purifier", 1 + (int)i));
	}
	tabs->setUsesScrollButtons(false);

	mainLayout->addWidget(tabs);
	DataUI::initWidget();
}

void PurifierUI::parseData(void) {
	if (purifier == NULL) return;
	for (size_t i = 0; i < 9; ++i) {
		chamberFlds[i]->chamber = purifier->chambers[i];
		chamberFlds[i]->chamberIndex = i;
		chamberFlds[i]->parseData();
	}
}

void PurifierUI::saveChanges(void) {
	for (size_t i = 0; i < 9; ++i)
		chamberFlds[i]->saveChanges();
}

void PurifierUI::cancelChanges(void) {
	for (size_t i = 0; i < 9; ++i)
		chamberFlds[i]->saveChanges();
}



}