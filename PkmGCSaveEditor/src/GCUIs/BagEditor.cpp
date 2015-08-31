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

#include <GCUIs/BagEditor.h>

using namespace LibPkmGC;
namespace GCUIs {

BagEditor::BagEditor(LibPkmGC::GC::BagData* inBag, QWidget* parent) : QWidget(parent), bag(inBag) {
	init();
}

BagEditor::~BagEditor(void){
	if (!isXD) delete battleCDsPocket;
}

void BagEditor::initWidget(void) {
	mainLayout = new QVBoxLayout;
	tabs = new QTabWidget;


	// pokeballs, TMs, berries and colognes do not have to take isXD into account 

	regularItemsPocket = new ItemPocketEditor(NULL, 0, REGULAR_ITEMS_ALLOWED);
	keyItemsPocket = new ItemPocketEditor(NULL, 43, KEY_ITEMS_ALLOWED);

	pokeballsPocket = new ItemPocketEditor(NULL, 16, POKEBALLS_ALLOWED);
	TMsPocket = new ItemPocketEditor(NULL, 64, TMS_ALLOWED);
	berriesPocket = new ItemPocketEditor(NULL, 46, BERRIES_ALLOWED);
	colognesPocket = new ItemPocketEditor(NULL, 3, COLOGNES_ALLOWED);
	battleCDsPocket = new ItemPocketEditor(NULL, 60, BATTLE_CDS_ALLOWED, true);

	tabs->addTab(regularItemsPocket, tr("Regular items"));
	tabs->addTab(keyItemsPocket, tr("Key items"));
	tabs->addTab(pokeballsPocket, tr("Pok\xc3\xa9""balls"));
	tabs->addTab(TMsPocket, tr("TMs"));
	tabs->addTab(berriesPocket, tr("Berries"));
	tabs->addTab(colognesPocket, tr("Colognes"));
	
	tabs->setUsesScrollButtons(false);
	mainLayout->addWidget(tabs);
	this->setLayout(mainLayout);
}

void BagEditor::parseData(void){
	if (bag == NULL) return;
	isXD = LIBPKMGC_IS_XD(BagData, bag);

	int c = tabs->count();
	battleCDsPocket->pocket = NULL;
	
	if (isXD) {
		XD::BagData* bag_xd = (XD::BagData*) bag;
		battleCDsPocket->pocket = bag_xd->battleCDs;
		battleCDsPocket->parseData();
		if(c != 7) tabs->addTab(battleCDsPocket, tr("Battle CDs"));
	}
	if (!isXD && (c == 7)) tabs->removeTab(6);

#define ST(pkt)  pkt##Pocket->pocket = bag->pkt; pkt##Pocket->isXD = isXD; pkt##Pocket->parseData();
	regularItemsPocket->pocketMaxSize = bag->nbRegularItems;
	
	ST(regularItems);
	ST(keyItems);
	ST(pokeballs);
	ST(TMs);
	ST(berries);
	ST(colognes);
#undef ST
}

void BagEditor::saveChanges(void){
	regularItemsPocket->saveChanges();
	keyItemsPocket->saveChanges();
	pokeballsPocket->saveChanges();
	TMsPocket->saveChanges();
	berriesPocket->saveChanges();
	colognesPocket->saveChanges();
	if (isXD) battleCDsPocket->saveChanges();
}



}