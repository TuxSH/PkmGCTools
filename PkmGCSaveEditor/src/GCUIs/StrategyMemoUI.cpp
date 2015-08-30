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
	strategyMemo->nbEntries = strategyMemo->recount();
	nbEntriesFld->setUnsignedValue(strategyMemo->nbEntries);
}

}