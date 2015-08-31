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

#include <GCUIs/PokemonBoxEditor.h>

using namespace LibPkmGC;
namespace GCUIs {

PokemonBoxEditor::PokemonBoxEditor(LibPkmGC::GC::PokemonBox* inBox, size_t inBoxNb, QWidget* parent) : QWidget(parent), box(inBox), boxNb(inBoxNb){
	init();
}


PokemonBoxEditor::~PokemonBoxEditor(void) {
}

void PokemonBoxEditor::initWidget(void) {
	mainLayout = new QVBoxLayout;
	nameLayout = new QFormLayout;
	nameFld = new QLineEdit;
	tabs = new QTabWidget;

	QString tmpl(tr("%1 to %2"));
	for (size_t i = 0; i < 5; ++i) {
		pages[i] = new QWidget;
		pageLayouts[i] = new QVBoxLayout;
		for (size_t j = 0; j < 6; ++j) {
			pkmFlds[6 * i + j] = new PokemonDisplayWidget;
			pageLayouts[i]->addWidget(pkmFlds[6 * i + j]);
		}
		connect(nameFld, SIGNAL(textChanged(QString const&)), this, SLOT(nameChangedEmitter(QString const&)));
		pages[i]->setLayout(pageLayouts[i]);
		tabs->addTab(pages[i], tmpl.arg(1 + 6 * i).arg(6 + 6 * i));
	}
	nameFld->setMaxLength(8);
	nameLayout->addRow(tr("Box name"), nameFld);
	mainLayout->addLayout(nameLayout);
	mainLayout->addWidget(tabs);
	this->setLayout(mainLayout);

}

void PokemonBoxEditor::parseData(void) {
	if (box == NULL) return;
	isXD = LIBPKMGC_IS_XD(PokemonBox, box);

	nameFld->setText(box->name->toUTF8());

	for (size_t i = 0; i < 30; ++i) {
		PokemonStorageInfo loc = { StoredInPC, boxNb, i };
		pkmFlds[i]->location = loc;
		pkmFlds[i]->pkm = (GC::Pokemon*)box->pkm[i];
		pkmFlds[i]->parseData();
	}
}

void PokemonBoxEditor::saveChanges(void) {
	box->name->fromUTF8(nameFld->text().toUtf8().data());
	for (size_t i = 0; i < 30; ++i)
		pkmFlds[i]->saveChanges();
}

void PokemonBoxEditor::cancelChanges(void) {
	for (size_t i = 0; i < 30; ++i)
		pkmFlds[i]->cancelChanges();
}

QString PokemonBoxEditor::currentBoxName(void) const {
	return nameFld->text();
}


void PokemonBoxEditor::nameChangedEmitter(QString const & newName) {
	emit nameChanged(boxNb, newName);
}


}