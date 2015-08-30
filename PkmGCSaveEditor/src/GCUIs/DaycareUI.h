#ifndef _PKMGCSAVEEDITOR_DAYCARE_UI_H
#define _PKMGCSAVEEDITOR_DAYCARE_UI_H

#include <GCUIs/PokemonDisplayWidget.h>

namespace GCUIs {

class DaycareUI : public DataUI {
	Q_OBJECT
public:
	DaycareUI(LibPkmGC::GC::DaycareData* inDaycare = NULL, QWidget* parent = NULL, Qt::WindowFlags f = Qt::Window);

	LibPkmGC::GC::DaycareData* daycare;

	void parseData(void);
	void saveChanges(void);
	void cancelChanges(void);
protected:
	void initWidget(void);

private:
	QFormLayout* daycareLayout;
	
	QButtonGroup* daycareStatusButtonGroup;
	QHBoxLayout* daycareStatusButtonLayout;
	QRadioButton *notVisitedButton, *emptyButton, *pkmDepositedButton;

	UnsignedSpinbox<7>* pkmInitialLevelFld;
	UnsignedSpinbox<32>* pkmInitialPurifCtrFld;
	// Cost of daycare : 100*(1 + (currentLevel - initialLevel) + 1 + int((purifCtr - initialPurifCtr)/100)) 
	// or 100*(1 + currentLevel - initialLvl) if (purifCtr - initialPurifCtr) < 100. 0 if status != PkmDeposited
	


	PokemonDisplayWidget *pkmFld;

};

}

#endif