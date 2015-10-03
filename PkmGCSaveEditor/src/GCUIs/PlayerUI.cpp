/*
* Copyright (C) TuxSH 2015
* This file is part of PkmGCSaveEditor.
*
* PkmGCSaveEditor is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* PkmGCSaveEditor is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with PkmGCSaveEditor.  If not, see <http://www.gnu.org/licenses/>.
*/

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
	ruisNameFld = new QLineEdit;

	ruisNameFld->setMaxLength(10);
	trainerInfoFld->addRow(tr("Rui's name"), ruisNameFld);

	trainerInfoBox->setLayout(trainerInfoFld);


	currenciesBox = new QGroupBox(tr("Currencies"));
	currenciesLayout = new QFormLayout;
	pokeDollarsFld = new UnsignedSpinbox<32>;
	pokeCouponsFld = new UnsignedSpinbox<32>;

	currenciesLayout->addRow(tr("Pok\xc3\xa9""dollars"), pokeDollarsFld);
	currenciesLayout->addRow(tr("Pok""\xc3\xa9""Coupons"), pokeCouponsFld); // Pokécoupons

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
}

void PlayerUI::parseData(void){
	if (player == NULL) return;
	isXD = LIBPKMGC_IS_XD(PlayerData, player);

	ruisNameFld->setVisible(!isXD);
	trainerInfoFld->labelForField(ruisNameFld)->setVisible(!isXD);

	if (!isXD) {
		ruisNameFld->setText(replaceSpecialNameCharsIn(static_cast<Colosseum::PlayerData*>(player)->ruisName->toUTF8()));
	}

	trainerInfoFld->set(player->trainer->trainerName, player->trainer->TID, player->trainer->SID, player->trainerGender);
	pokeDollarsFld->setValue((int)player->pokeDollars);
	pokeCouponsFld->setValue((int)player->pokeCoupons);

	bagTab->bag = player->bag;
	bagTab->parseData();

	for (size_t i = 0; i < 6; ++i) {
		PokemonStorageInfo loc = { StoredInParty, i, 0 };
		pkmFlds[i]->location = loc;
		pkmFlds[i]->pkm = player->trainer->party[i];
		pkmFlds[i]->parseData();
	}

}

void PlayerUI::saveChanges(void) {
	if (!isXD)
		static_cast<Colosseum::PlayerData*>(player)->ruisName->fromUTF8(replaceSpecialNameCharsOut(ruisNameFld->text()).toUtf8().data());
	trainerInfoFld->trainerName(player->trainer->trainerName);
	player->trainer->TID = trainerInfoFld->TID();
	player->trainer->SID = trainerInfoFld->SID();
	player->trainerGender = trainerInfoFld->trainerGender();
	player->pokeDollars = pokeDollarsFld->unsignedValue();
	player->pokeCoupons = pokeCouponsFld->unsignedValue();

	for (size_t i = 0; i < 6; ++i) pkmFlds[i]->saveChanges();
	bagTab->saveChanges();

}

void PlayerUI::cancelChanges(void) {
	for (size_t i = 0; i < 6; ++i) pkmFlds[i]->cancelChanges();
}

void PlayerUI::pkmDeletionHandler(LibPkmGC::PokemonStorageInfo const & location) {
	size_t i = location.index;
	GC::Pokemon *party2[6] = { NULL };
	GC::Pokemon *deltd = player->trainer->party[i];
	std::copy(player->trainer->party, player->trainer->party + i, party2);
	std::copy(player->trainer->party + i + 1, player->trainer->party + 6, party2 + i);
	std::copy(party2, party2 + 5, player->trainer->party);
	player->trainer->party[5] = deltd;
	for (size_t i = 0; i < 6; ++i) {
		PokemonStorageInfo loc = { StoredInParty, i, 0 };
		pkmFlds[i]->location = loc;
		pkmFlds[i]->pkm = player->trainer->party[i];
		pkmFlds[i]->parseData();
	}
}

}