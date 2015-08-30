#ifndef _PKMGCSAVEEDITOR_PC_UI_H
#define _PKMGCSAVEEDITOR_PC_UI_H

#include <Core/ItemPocketEditor.h>
#include <GCUIs/PokemonBoxEditor.h>

namespace GCUIs {

class PCUI : public DataUI {
	Q_OBJECT
public:
	PCUI(LibPkmGC::GC::PCData* inPC = NULL, QWidget* parent = NULL, Qt::WindowFlags f = Qt::Window);

	LibPkmGC::GC::PCData* PC;

	void parseData(void);
	void saveChanges(void);
	void cancelChanges(void);
public slots:
	void boxNameChangeHandler(size_t nb, QString const& newName);
protected:
	void initWidget(void);

private:
	QTabWidget* tabs;

	QVBoxLayout*  pkmStorageTabLayout;
	QWidget* pkmStorageTab;
	QFormLayout* boxSelectorLayout;
	QComboBox* boxSelector;
	QStackedWidget* boxes;


	ItemPocketEditor* itemsTab;
};

}

#endif