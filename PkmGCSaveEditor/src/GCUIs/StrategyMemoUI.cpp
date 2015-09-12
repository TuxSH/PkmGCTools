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

#include <GCUIs/StrategyMemoUI.h>

using namespace LibPkmGC;
using namespace Localization;

namespace GCUIs {


StrategyMemoUI::StrategyMemoUI(GC::StrategyMemoData* inStrategyMemo, QWidget* parent, Qt::WindowFlags f) : DataUI(parent, f), strategyMemo(inStrategyMemo),
strategyMemoBackup(NULL){
	init();
}

StrategyMemoUI::~StrategyMemoUI(void) {
	delete strategyMemoBackup;
}

void StrategyMemoUI::initWidget(void) {
	LanguageIndex lg = generateDumpedNamesLanguage();
	entrySelectorLayout = new QFormLayout;
	entrySelector = new QComboBox;

	nbEntriesFld = new UnsignedSpinbox<16>;
	nbEntriesFld->setDisabled(true);
	currentEntry = new StrategyMemoEntryWidget;
	connect(currentEntry, SIGNAL(speciesChanged(int, size_t)), this, SLOT(updateEntryNameAndNbEntries(int, size_t)));

	QString tmpl(tr("#%1: %2"));

	for (size_t i = 0; i < 500; ++i)
		entrySelector->addItem(tmpl.arg((int)i).arg(getPokemonSpeciesName(lg, NoSpecies)));

	entrySelectorLayout->addRow(tr("Number of entries"), nbEntriesFld);
	entrySelectorLayout->addRow(tr("Entry"), entrySelector);
	mainLayout->addLayout(entrySelectorLayout);
	mainLayout->addStretch();
	mainLayout->addWidget(currentEntry);
	mainLayout->addStretch();
	DataUI::initWidget();

	connect(entrySelector, SIGNAL(currentIndexChanged(int)), this, SLOT(setCurrentEntry(int)));
}

void StrategyMemoUI::updateEntryName(int index, size_t nameIndex) {
	LanguageIndex lg = generateDumpedNamesLanguage();
	QString tmpl(tr("#%1: %2"));

	entrySelector->setItemText(index, tmpl.arg(index+1).arg(getPokemonSpeciesName(lg, nameIndexToPkmSpeciesIndex(nameIndex))));
}



void StrategyMemoUI::parseData(void) {
	if (strategyMemo == NULL) return;
	if (strategyMemoBackup == NULL) strategyMemoBackup = strategyMemo->clone();
	isXD = strategyMemo->isXD();
	for (int i = 0; i < 500; ++i) {
		updateEntryName(i, pkmSpeciesIndexToNameIndex(strategyMemo->entries[i]->species));
	}
	updateEntryNameAndNbEntries(0, pkmSpeciesIndexToNameIndex(strategyMemo->entries[0]->species));
	setCurrentEntry(0);
}

void StrategyMemoUI::saveChanges(void) {
	currentEntry->saveChanges();
	delete strategyMemoBackup;
	strategyMemoBackup = strategyMemo->clone();
}

void StrategyMemoUI::cancelChanges(void) {
	*strategyMemo = *strategyMemoBackup;
}

void StrategyMemoUI::setCurrentEntry(int index) {
	if (currentEntry->entry != NULL) currentEntry->saveChanges();
	currentEntry->entry = strategyMemo->entries[index];
	currentEntry->entryIndex = index;
	currentEntry->parseData();
}


void StrategyMemoUI::updateEntryNameAndNbEntries(int index, size_t nameIndex) {
	updateEntryName(index, nameIndex);
	strategyMemo->entries[index]->species = nameIndexToPkmSpeciesIndex(nameIndex);
	strategyMemo->nbEntries = (u16) strategyMemo->recount();
	nbEntriesFld->setUnsignedValue(strategyMemo->nbEntries);
}

}