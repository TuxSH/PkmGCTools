#include <GCUIs/DaycareUI.h>

namespace GCUIs {

using namespace LibPkmGC;
DaycareUI::DaycareUI(LibPkmGC::GC::DaycareData * inDaycare, QWidget * parent, Qt::WindowFlags f) : DataUI(parent, f), daycare(inDaycare) {
	init();
}

void DaycareUI::initWidget(void) {
	daycareLayout = new QFormLayout;
	
	daycareStatusButtonLayout = new QHBoxLayout; // NotVisited = -1, NoPkmDeposited = 0, PkmDeposited = 1
	daycareStatusButtonGroup = new QButtonGroup;
	notVisitedButton = new QRadioButton(tr("Not visited yet"));
	emptyButton = new QRadioButton(tr("Empty"));
	pkmDepositedButton = new QRadioButton(tr("Pok\xc3\xa9mon deposited"));

	pkmInitialLevelFld = new UnsignedSpinbox<7>;
	pkmInitialPurifCtrFld = new UnsignedSpinbox<32>;

	pkmInitialLevelFld->setRange(1, 100);
	
	PokemonStorageInfo loc = { StoredInDaycare, 0, 0 };
	pkmFld = new PokemonDisplayWidget(NULL, loc);

	daycareStatusButtonGroup->addButton(notVisitedButton, 0); daycareStatusButtonLayout->addWidget(notVisitedButton, 0);
	daycareStatusButtonGroup->addButton(emptyButton, 1); daycareStatusButtonLayout->addWidget(emptyButton, 1);
	daycareStatusButtonGroup->addButton(pkmDepositedButton, 2); daycareStatusButtonLayout->addWidget(pkmDepositedButton, 2);
	notVisitedButton->hide();
	emptyButton->setChecked(true);

	daycareLayout->addRow(tr("Daycare status"), daycareStatusButtonLayout);
	daycareLayout->addRow(tr("Initial Pok\xc3\xa9mon level"), pkmInitialLevelFld);
	daycareLayout->addRow(tr("Initial Pok\xc3\xa9mon purification counter"), pkmInitialPurifCtrFld);
	//daycareLayout->addRow(tr(""), pkmFld);
	mainLayout->addLayout(daycareLayout);
	mainLayout->addWidget(pkmFld);

	DataUI::initWidget();
}


void DaycareUI::parseData(void) {
	if (daycare == NULL) return;
	
	isXD = LIBPKMGC_IS_XD(DaycareData, daycare);
	notVisitedButton->setVisible(isXD);

	notVisitedButton->setChecked(daycare->status == NotVisited);
	emptyButton->setChecked(daycare->status == NoPkmDeposited);
	pkmDepositedButton->setChecked(daycare->status == PkmDeposited);

	pkmInitialLevelFld->setValue(daycare->initialPkmLevel);
	pkmInitialPurifCtrFld->setValue(daycare->initialPkmPurifCounter);

	pkmFld->pkm = daycare->pkm;
	pkmFld->parseData();
}

void DaycareUI::saveChanges(void) {
	daycare->status = (DaycareStatus)(daycareStatusButtonGroup->checkedId() - 1);
	daycare->initialPkmLevel = (u8)pkmInitialLevelFld->unsignedValue();
	daycare->initialPkmPurifCounter = pkmInitialPurifCtrFld->unsignedValue();

	pkmFld->saveChanges();
}

void DaycareUI::cancelChanges(void){
	pkmFld->cancelChanges();
}


}