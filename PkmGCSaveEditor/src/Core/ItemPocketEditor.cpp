#include <Core/ItemPocketEditor.h>
using namespace LibPkmGC;
using namespace Localization;

ItemPocketEditor::ItemPocketEditor(LibPkmGC::Item* inPocket, size_t inPocketMaxSize, unsigned int inFlags, bool inIsXD, QWidget* parent) : QWidget(parent),
IDataUI(), pocket(inPocket), pocketMaxSize(inPocketMaxSize), flags(inFlags), isXD(inIsXD), items(NULL) {
	init();
}


ItemPocketEditor::~ItemPocketEditor(void){
	delete[] items;
}

void ItemPocketEditor::initWidget(void) {
	mainLayout = new QVBoxLayout;
	tbl = new QTableWidget(0, 2);
	actionLayout = new QHBoxLayout;
	tbl->setHorizontalHeaderLabels(QStringList(tr("Item")) << tr("Quantity"));
	
	tbl->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	tbl->verticalHeader()->hide();
	tbl->setSelectionBehavior(QAbstractItemView::SelectRows);
	tbl->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	tbl->setEditTriggers(QAbstractItemView::NoEditTriggers);

	itemNameFld = new ItemComboBox;
	quantityFld = new UnsignedSpinbox<16>;
	modifyButton = new QPushButton(tr("Modify"));
	deleteButton = new QPushButton(tr("Delete"));

	actionLayout->addWidget(new QLabel(tr("Item")));
	actionLayout->addWidget(itemNameFld);
	actionLayout->addWidget(new QLabel(tr("Quantity")));
	actionLayout->addWidget(quantityFld);
	actionLayout->addWidget(modifyButton);
	actionLayout->addWidget(deleteButton);

	mainLayout->addWidget(tbl);
	mainLayout->addLayout(actionLayout);
	this->setLayout(mainLayout);

	QShortcut* shortcut = new QShortcut(QKeySequence(QKeySequence::Delete), this);
	connect(shortcut, SIGNAL(activated()), this, SLOT(deleteSelected()));


	connect(tbl, SIGNAL(currentItemChanged(QTableWidgetItem*, QTableWidgetItem*)), this, SLOT(displayItem()));
	connect(itemNameFld, SIGNAL(currentIndexChanged(int)), this, SLOT(updateMaxQuantity()));
	connect(modifyButton, SIGNAL(clicked(bool)), this, SLOT(modifySelected()));
	connect(deleteButton, SIGNAL(clicked(bool)), this, SLOT(deleteSelected()));
}

void ItemPocketEditor::setItemAt(int i) {
	LanguageIndex lg = generateDumpedNamesLanguage();

	QTableWidgetItem *qty = new QTableWidgetItem(QString::number(items[i].quantity));
	qty->setTextAlignment((int)Qt::AlignRight | (int)Qt::AlignVCenter);
	tbl->setItem(i, 0, new QTableWidgetItem(getItemName(lg, items[i].index, isXD)));
	tbl->setItem(i, 1, qty);
}


void ItemPocketEditor::parseData(void) {
	if (pocket == NULL) return;
	flags &= ~EMPTY_ITEM_FORBIDDEN;
	tbl->clearContents();
	
	delete[] items;
	items = new Item[pocketMaxSize];
	std::copy(pocket, pocket + pocketMaxSize, items);

	tbl->setRowCount((int)pocketMaxSize);
	for (size_t i = 0; i < pocketMaxSize; ++i)
		setItemAt((int)i);
	itemNameFld->set(flags, isXD);
	quantityFld->setDisabled(true);
}

void ItemPocketEditor::saveChanges(void) {
	std::copy(items, items + pocketMaxSize, pocket);
}

LibPkmGC::Item ItemPocketEditor::editedItem(void) const{
	Item item_ = { itemNameFld->currentItemIndex(), (u16) quantityFld->value() };
	return item_;
}

void ItemPocketEditor::setEditedItem(LibPkmGC::Item const & val){
	itemNameFld->setCurrentItemIndex(val.index);
	quantityFld->setValue(val.quantity);
}

void ItemPocketEditor::updateMaxQuantity(void) {
	const int maxqty[] = { 0, 99, 99, 99, 99, 1, 99, 1 };
	const int maxqtyPCOrXD[] = { 0, 999, 999, 999, 999, 1, 999, 1 };

	ItemCategoryIndex ctgy = getItemCategory(itemNameFld->currentItemIndex(), isXD);
	quantityFld->setRange(0, (isXD || flags == GIVABLE_ITEMS_ALLOWED) ? maxqtyPCOrXD[ctgy] : maxqty[ctgy]);
	quantityFld->setDisabled(maxqty[ctgy] == 0);
}
void ItemPocketEditor::displayItem(void) {
	QTableWidgetItem *it = tbl->currentItem();
	setEditedItem(items[it->row()]);
}

void ItemPocketEditor::modifySelected(void) {
	// All selected items will be modified
	QModelIndexList indices = tbl->selectionModel()->selectedIndexes();
	Item item_ = editedItem();

	for (int i = 0; i < indices.count(); ++i) {
		items[indices[i].row()] = item_;
		setItemAt(indices[i].row());
	}
}

void ItemPocketEditor::deleteSelected(void) {
	// All selected items will be deleted
	QModelIndexList indices = tbl->selectionModel()->selectedIndexes();
	Item* items2 = new Item[pocketMaxSize];
	std::fill(items2, items2 + pocketMaxSize, Item());

	int j = 0;
	for (size_t i = 0; i < pocketMaxSize; ++i) {
		if (!tbl->item((int)i, 0)->isSelected()) items2[j++] = items[i];
	}

	delete[] items;
	items = items2;
	for (size_t i = 0; i < pocketMaxSize; ++i)
		setItemAt((int)i);
	displayItem();
}


