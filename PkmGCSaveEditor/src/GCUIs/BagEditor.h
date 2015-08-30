#ifndef _PKMGCSAVEEDITOR_BAG_EDITOR_H
#define _PKMGCSAVEEDITOR_BAG_EDITOR_H

#include <Core/ItemPocketEditor.h>
#include <LibPkmGC/GC/Common/BagData.h>
#include <LibPkmGC/XD/Common/BagData.h>
#include <QTabWidget>

namespace GCUIs {

class BagEditor : public QWidget, public IDataUI {
	Q_OBJECT
public:
	BagEditor(LibPkmGC::GC::BagData* inBag = NULL, QWidget* parent = NULL);
	~BagEditor(void);
	void parseData(void);
	LibPkmGC::GC::BagData* bag;

	void saveChanges(void);

protected:
	void initWidget(void);

private:
	bool isXD;
	QVBoxLayout* mainLayout;
	QTabWidget* tabs;
	ItemPocketEditor *regularItemsPocket, *keyItemsPocket, *pokeballsPocket, *TMsPocket, *berriesPocket, *colognesPocket, *battleCDsPocket;
};

}

#endif