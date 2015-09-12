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

#include <GCUIs/PokemonDisplayWidget.h>

#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>

using namespace LibPkmGC;
using namespace Localization;

namespace GCUIs {

PokemonDisplayWidget::PokemonDisplayWidget(GC::Pokemon* inPkm, LibPkmGC::PokemonStorageInfo const& inLocation, QWidget* parent) :
	QWidget(parent), pkm(inPkm), location(inLocation), pkmBackup(NULL) {
	init();
}

PokemonDisplayWidget::~PokemonDisplayWidget(void) {
	delete pkmBackup;
}

void PokemonDisplayWidget::initWidget(void) {
	mainLayout = new QHBoxLayout;
	buttonsLayout = new QHBoxLayout;
	nameFld = new QLabel;
	summary = new QLabel;
	editButton = new QPushButton(tr("Edit"));
	deleteButton = new QPushButton(tr("Delete"));
	importButton = new QPushButton(tr("Import"));
	exportButton = new QPushButton(tr("Export"));

	mainLayout->addWidget(nameFld);
	mainLayout->addWidget(summary);
	buttonsLayout->addWidget(editButton);
	buttonsLayout->addWidget(deleteButton);
	buttonsLayout->addWidget(importButton);
	buttonsLayout->addWidget(exportButton);
	mainLayout->addLayout(buttonsLayout);

	connect(editButton, SIGNAL(clicked()), this, SLOT(openPkmUI()));
	connect(deleteButton, SIGNAL(clicked()), this, SLOT(deletePkm()));

	connect(importButton, SIGNAL(clicked()), this, SLOT(openImportPkmDialog()));
	connect(exportButton, SIGNAL(clicked()), this, SLOT(openExportPkmDialog()));
	this->setLayout(mainLayout);
}

void PokemonDisplayWidget::parseData(void) {
	if (pkm == NULL) return;
	if (pkmBackup == NULL) pkmBackup = pkm->clone();

	updatePkmNameAndSummary();
}

void PokemonDisplayWidget::saveChanges(void) {
	delete pkmBackup; 	// PokemonUI::saveChanges has been called already, we don't need to call it again
	pkmBackup = pkm->clone();
}

void PokemonDisplayWidget::cancelChanges(void) {
	*pkm = *pkmBackup;
}

void PokemonDisplayWidget::updatePkmNameAndSummary(void) {
	LanguageIndex lg = generateDumpedNamesLanguage();
	QString s, tt;

	if (pkm == NULL || pkm->species == NoSpecies) {
		nameFld->setText(getPokemonSpeciesName(lg, (pkm == NULL) ? NoSpecies : pkm->species));
		summary->setText("");
		return;
	}

	nameFld->setText(pkm->name->toUTF8());

	s = "(";
	if (!getSpeciesData(pkm->species).isValid || (pkm->species == Bonsly && !LIBPKMGC_IS_XD(Pokemon,pkm))) {
		tt = tr("Invalid species");
	}
	if (pkm->version.isIncomplete()) {
		if (!tt.isEmpty()) tt += "\n";
		tt = tr("Invalid version info");
	}
	if (pkm->pkmFlags[LIBPKMGC_GC_INVALID_POKEMON_FLAG]) {
		if (!tt.isEmpty()) tt += "\n";
		tt += tr("\"Invalid Pok\xc3\xa9mon\" flag set");
	}

	summary->setToolTip(tt);
	
	if (!tt.isEmpty()) {
		s += "<span style='color:red;'>INVALID</span>";
	}
	else {
		s += tr("Lv. %n ", "", (pkm->partyData.level > 100) ? 100 : pkm->partyData.level);
		s += PokemonUI::getShortPkmAttributeText(pkm->species, pkm->PID, pkm->TID, pkm->SID);
	}
	s += ")";

	summary->setText(s);
}


void PokemonDisplayWidget::openPkmUI(void) {
	PokemonUI dlg(pkm, location, this);
	if (dlg.exec() == 1) {
		updatePkmNameAndSummary();
		emit pkmUpdated(pkm, location);
	}
}

void PokemonDisplayWidget::deletePkm(void) {
	std::fill(pkm->data, pkm->data + pkm->fixedSize, 0);
	pkm->reload();
	emit pkmDeleted(location);
	updatePkmNameAndSummary();
}



QString PokemonDisplayWidget::selectFilters(bool op) {
	const QString allsupportedfilesfilter = tr("All supported files (*.colopkm *.xdpkm *.pkm *.3gpkm)");
	const QString colofilter = tr("Colosseum Pok\xc3\xa9mon files (*.colopkm)");
	const QString xdfilter = tr("XD Pok\xc3\xa9mon files (*.xdpkm)");
	const QString gbafilter = tr("GBA Pok\xc3\xa9mon files (*.pkm *.3gpkm)");
	const QString gbaencfilter = tr("Encrypted GBA Pok\xc3\xa9mon files (*.pkm *.3gpkm)");
	const QString allfilesfilter = tr("All files (*)");
	QString F[] = { colofilter, xdfilter, gbafilter };
	if (pkm != NULL) {
		if (LIBPKMGC_IS_GBA(Pokemon, pkm)) std::swap(F[0], F[2]);
		else if (LIBPKMGC_IS_XD(Pokemon, pkm)) std::swap(F[0], F[1]);
	}
	return (op) ? (allsupportedfilesfilter + ";;" + F[0] + ";;" + F[1] + ";;" + F[2]) :
		(F[0] + ";;" + F[1] + ";;" + F[2] + ";;" + gbaencfilter);
}

void PokemonDisplayWidget::openImportPkmDialog(void) {
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Pok\xc3\xa9mon file"), lastPkmDirectory, selectFilters(true));
	if (fileName.isEmpty()) return;

	QFileInfo fileInfo(fileName);
	size_t fileSize = (size_t) fileInfo.size();

	switch (fileSize) {
	case 0x138: readExpected<Colosseum::Pokemon>(fileName); break;
	case 0xc4: readExpected<XD::Pokemon>(fileName); break;
	case 100: case 80: readExpected<GBA::Pokemon>(fileName, fileSize); break;
	default: QMessageBox::critical(this, tr("Error"), tr("Invalid file size.")); break;
	}

}

void PokemonDisplayWidget::openExportPkmDialog(void) {
	const QString errmsg = tr("Could not write to file.");
	const QString errmsg2 = tr("An error occured while writing to the specified Pok\xc3\xa9mon file.");
	const QString gbaencfilter = tr("Encrypted GBA Pok\xc3\xa9mon files (*.pkm *.3gpkm)");

	QString selectedFilter;
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Pok\xc3\xa9mon file"), lastPkmDirectory, selectFilters(false), &selectedFilter);
	if (fileName.isEmpty()) return;
	
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly)) {
		QMessageBox::critical(this, tr("Error"), errmsg);
		return;
	}

	QString selectedExt = fileName.section(".", -1);

	
	Base::Pokemon* exportedPkm = pkm;
	bool created = false;
	
	if ((selectedExt == "colopkm") && !LIBPKMGC_IS_COLOSSEUM(Pokemon, pkm)) {
		exportedPkm = new Colosseum::Pokemon(*(XD::Pokemon*)pkm);
		created = true;
	}
	else if ((selectedExt == "xdpkm") && !LIBPKMGC_IS_XD(Pokemon, pkm)) {
		exportedPkm = new XD::Pokemon(*(Colosseum::Pokemon*)pkm);
		created = true;
	}
	else if ((selectedExt == "3gpkm" || selectedExt == "pkm") && !LIBPKMGC_IS_GBA(Pokemon, pkm)) {
		exportedPkm = new GBA::Pokemon(*pkm);
		created = true;
	}

	exportedPkm->save();

	char* dta = (char*)exportedPkm->data;
	QByteArray dt(100, 0);

	if (selectedFilter == gbaencfilter) {
		static_cast<GBA::Pokemon*>(exportedPkm)->saveEncrypted((u8*)dt.data());
		dta = dt.data();
	}

	if (file.write(dta, exportedPkm->fixedSize) != (qint64)exportedPkm->fixedSize)
		QMessageBox::critical(this, tr("Error"), errmsg2);
	else
		lastPkmDirectory = QFileInfo(fileName).canonicalPath();
	
	if (created) delete exportedPkm;

}

}