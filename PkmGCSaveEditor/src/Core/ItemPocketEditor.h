#ifndef _PKMGCSAVEEDITOR_ITEM_POCKET_EDITOR
#define _PKMGCSAVEEDITOR_ITEM_POCKET_EDITOR

#include <Core/ItemComboBox.h>
#include <Core/UnsignedSpinbox.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <Core/IDataUI.h>
#include <QPushButton>
#include <QTableWidget>
#include <QLabel>
#include <QHeaderView>
#include <QComboBox>
#include <QShortcut>

class ItemPocketEditor : public QWidget, public IDataUI {
	Q_OBJECT
public:
	ItemPocketEditor(LibPkmGC::Item* inPocket = NULL, size_t inPocketMaxSize = 0, unsigned int inFlags = 0, bool inIsXD = false, QWidget* parent = NULL);
	~ItemPocketEditor(void);

	LibPkmGC::Item* pocket;
	size_t pocketMaxSize;
	unsigned int flags;
	bool isXD;

	void parseData(void);
	void saveChanges(void);

	LibPkmGC::Item editedItem(void) const;
	void setEditedItem(LibPkmGC::Item const& val);
public slots:
	void updateMaxQuantity(void);
	void displayItem(void);
	void modifySelected(void);
	void deleteSelected(void);
protected:
	void initWidget(void);
private:
	void setItemAt(int i);
	LibPkmGC::Item *items;
	QVBoxLayout* mainLayout;
	QTableWidget* tbl;

	QHBoxLayout* actionLayout;
	ItemComboBox *itemNameFld;
	UnsignedSpinbox<8> *quantityFld;
	QPushButton *modifyButton, *deleteButton;
};

#endif