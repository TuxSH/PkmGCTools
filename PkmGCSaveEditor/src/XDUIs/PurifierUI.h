#ifndef _PKMGCSAVEEDITOR_PURIFIER_UI_H
#define _PKMGCSAVEEDITOR_PURIFIER_UI_H

#include <GCUIs/PokemonDisplayWidget.h>

namespace XDUIs {

class PurificationChamberWidget : public QWidget, public IDataUI {
	Q_OBJECT
public:
	PurificationChamberWidget(LibPkmGC::XD::PurificationChamber* inChamber = NULL, size_t inChamberIndex = 0, QWidget* parent = NULL);

	LibPkmGC::XD::PurificationChamber* chamber;
	size_t chamberIndex;

	void parseData(void);
	void saveChanges(void);
	void cancelChanges(void);

protected:
	void initWidget(void);

private:
	QVBoxLayout* mainLayout;
	
	GCUIs::PokemonDisplayWidget* normalPkmFlds[3];

	GCUIs::PokemonDisplayWidget* shadowPkmFld;

};

class PurifierUI : public DataUI {
	Q_OBJECT
public:
	PurifierUI(LibPkmGC::XD::PurifierData* inPurifier = NULL, QWidget* parent = NULL, Qt::WindowFlags f = Qt::Window);

	LibPkmGC::XD::PurifierData* purifier;

	void parseData(void);
	void saveChanges(void);
	void cancelChanges(void);

protected:
	void initWidget(void);

private:
	QTabWidget* tabs;
	PurificationChamberWidget *chamberFlds[9];

};

}

#endif