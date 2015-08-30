#include <GCUIs/PCUI.h>

using namespace LibPkmGC;

namespace GCUIs {

PCUI::PCUI(LibPkmGC::GC::PCData* inPC, QWidget* parent, Qt::WindowFlags f) : DataUI(parent, f), PC(inPC) {
	init();
}


void PCUI::initWidget(void) {
	tabs = new QTabWidget;

	pkmStorageTab = new QWidget;
	pkmStorageTabLayout = new QVBoxLayout;
	boxSelectorLayout = new QFormLayout;
	boxSelector = new QComboBox;
	boxes = new QStackedWidget;

	itemsTab = new ItemPocketEditor(NULL, 0xeb, GIVABLE_ITEMS_ALLOWED);

	boxSelectorLayout->addRow(tr("Selected box"), boxSelector);
	pkmStorageTabLayout->addLayout(boxSelectorLayout);
	pkmStorageTabLayout->addWidget(boxes);
	pkmStorageTab->setLayout(pkmStorageTabLayout);

	tabs->addTab(pkmStorageTab, tr("Pok\xc3\xa9mon"));
	tabs->addTab(itemsTab, tr("Items"));

	mainLayout->addWidget(tabs);
	DataUI::initWidget();

	connect(boxSelector, SIGNAL(currentIndexChanged(int)), boxes, SLOT(setCurrentIndex(int)));
}

void PCUI::parseData(void) {
	if (PC == NULL) return;
	isXD = LIBPKMGC_IS_XD(PCData, PC);
	
	int nb = (int) PC->nbBoxes;
	int c = boxes->count();
	for (int i = 0; i < c; ++i) {
		QWidget* w = boxes->widget(i);
		boxes->removeWidget(w);
		delete w;
	}
	boxSelector->clear();
	for (int i = 0; i < nb; ++i) {
		PokemonBoxEditor* box = new PokemonBoxEditor(PC->boxes[i], (size_t)i);
		boxes->addWidget(box);
		boxSelector->addItem(box->currentBoxName(), i);
		connect(box, SIGNAL(nameChanged(size_t, QString const&)), this, SLOT(boxNameChangeHandler(size_t, QString const&)));
	}

	itemsTab->pocket = PC->items;
	itemsTab->isXD = isXD;
	itemsTab->parseData();
}

void PCUI::saveChanges(void) {
	for (size_t i = 0; i < PC->nbBoxes; ++i) {
		PokemonBoxEditor* box = (PokemonBoxEditor*)boxes->widget((int)i);
		box->saveChanges();
	}
	itemsTab->saveChanges();
}

void PCUI::cancelChanges(void) {
	for (size_t i = 0; i < PC->nbBoxes; ++i) {
		PokemonBoxEditor* box = (PokemonBoxEditor*)boxes->widget((int)i);
		box->cancelChanges();
	}
}

void PCUI::boxNameChangeHandler(size_t nb, QString const & newName) {
	boxSelector->setItemText((int)nb, newName);
}

}