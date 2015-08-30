#include <GCUIs/PlayerUI.h>

using namespace LibPkmGC;

namespace GCUIs{

PlayerUI::PlayerUI(LibPkmGC::GC::PlayerData* inPlayer, QWidget* parent, Qt::WindowFlags f) : DataUI(parent, f), player(inPlayer) {
	init();
}

void PlayerUI::initWidget(void){
	tabs = new QTabWidget;
	
	generalTab = new QWidget;
	generalTabLayout = new QVBoxLayout;
	trainerInfoBox = new QGroupBox(tr("Trainer information"));
	trainerInfoFld = new TrainerInfoLayout;

	trainerInfoBox->setLayout(trainerInfoFld);

	currenciesBox = new QGroupBox(tr("Currencies"));
	currenciesLayout = new QFormLayout;
	moneyFld = new UnsignedSpinbox<32>;
	pkCouponsFld = new UnsignedSpinbox<32>;

	currenciesLayout->addRow(tr("Money"), moneyFld);
	currenciesLayout->addRow(tr("Pok""\xc3\xa9""coupons"), pkCouponsFld); // Pokécoupons

	currenciesBox->setLayout(currenciesLayout);

	generalTabLayout->addWidget(trainerInfoBox);
	generalTabLayout->addWidget(currenciesBox);
	generalTab->setLayout(generalTabLayout);

	bagTab = new BagEditor;

	partyTab = new QWidget;
	partyTabLayout = new QVBoxLayout;
	partyTabLayout->addStretch();
	for (size_t i = 0; i < 6; ++i) {
		pkmFlds[i] = new PokemonDisplayWidget;
		partyTabLayout->addWidget(pkmFlds[i]);
		connect(pkmFlds[i], SIGNAL(pkmDeleted(LibPkmGC::PokemonStorageInfo const&)), this, SLOT(pkmDeletionHandler(LibPkmGC::PokemonStorageInfo const&)));
	}
	partyTabLayout->addStretch();

	partyTab->setLayout(partyTabLayout);

	tabs->addTab(generalTab, tr("General"));
	tabs->addTab(bagTab, tr("Bag"));
	tabs->addTab(partyTab, tr("Party"));
	mainLayout->addWidget(tabs);
	DataUI::initWidget();
}

PlayerUI::~PlayerUI(void){
	//for (size_t i = 0; i < 6; ++i) delete partyBackup[i];
}

void PlayerUI::parseData(void){
	if (player == NULL) return;
	isXD = LIBPKMGC_IS_XD(PlayerData, player);

	trainerInfoFld->set(player->trainerName, player->TID, player->SID, player->trainerGender);
	moneyFld->setValue((int)player->money);
	pkCouponsFld->setValue((int)player->pkCoupons);

	bagTab->bag = player->bag;
	bagTab->parseData();

	for (size_t i = 0; i < 6; ++i) {
		PokemonStorageInfo loc = { StoredInParty, i, 0 };
		pkmFlds[i]->location = loc;
		pkmFlds[i]->pkm = player->party[i];
		pkmFlds[i]->parseData();
	}

}

void PlayerUI::saveChanges(void) {
	trainerInfoFld->trainerName(player->trainerName);
	player->TID = trainerInfoFld->TID();
	player->SID = trainerInfoFld->SID();
	player->trainerGender = trainerInfoFld->trainerGender();
	player->money = moneyFld->unsignedValue();
	player->pkCoupons = pkCouponsFld->unsignedValue();

	for (size_t i = 0; i < 6; ++i) pkmFlds[i]->saveChanges();
	bagTab->saveChanges();

}

void PlayerUI::cancelChanges(void) {
	for (size_t i = 0; i < 6; ++i) pkmFlds[i]->cancelChanges();
}

void PlayerUI::pkmDeletionHandler(LibPkmGC::PokemonStorageInfo const & location) {
	size_t i = location.index;
	GC::Pokemon *party2[6] = { NULL };
	GC::Pokemon *deltd = player->party[i];
	std::copy(player->party, player->party + i, party2);
	std::copy(player->party + i + 1, player->party + 6, party2 + i);
	std::copy(party2, party2 + 5, player->party);
	player->party[5] = deltd;
	for (size_t i = 0; i < 6; ++i) {
		PokemonStorageInfo loc = { StoredInParty, i, 0 };
		pkmFlds[i]->location = loc;
		pkmFlds[i]->pkm = player->party[i];
		pkmFlds[i]->parseData();
	}
}

}