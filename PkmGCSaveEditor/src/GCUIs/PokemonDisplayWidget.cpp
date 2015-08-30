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
	if (!getSpeciesData(pkm->species).isValid) {
		tt = tr("Invalid species");
	}
	if (pkm->version.isIncomplete()) {
		if (!tt.isEmpty()) tt += "\n";
		tt = tr("Invalid version info");
	}
	if (LIBPKMGC_IS_XD(Pokemon, pkm) && (static_cast<XD::Pokemon*>(pkm)->pkmFlags & 0x20) != 0) {
		if (!tt.isEmpty()) tt += "\n";
		tt += tr("Bit 5 set on byte at offset 0x1d");
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



QString PokemonDisplayWidget::selectFilters(void) {
	const QString colofilter = tr("Colosseum Pok\xc3\xa9mon files (*.colopkm)");
	const QString xdfilter = tr("XD Pok\xc3\xa9mon files (*.xdpkm)");
	const QString allfilesfilter = tr("All files (*)");
	return ((pkm == NULL || LIBPKMGC_IS_COLOSSEUM(Pokemon, pkm)) ?
		colofilter + ";;" + xdfilter + ";;" + allfilesfilter :
		xdfilter + ";;" + colofilter + ";;" + allfilesfilter);
}
 
void PokemonDisplayWidget::openImportPkmDialog(void) {
	const QString errmsg = tr("Could not open file.");
	const QString errmsg2 = tr("An error occured while reading the specified Pok\xc3\xa9mon file.");

	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Pok\xc3\xa9mon file"), lastPkmDirectory, selectFilters());
	if (fileName.isEmpty()) return;

	QFileInfo fileInfo(fileName);
	size_t fileSize = (size_t) fileInfo.size();
	if (fileSize == 0x138) { // Colosseum Pokémon
		QFile file(fileName);
		if (!file.open(QIODevice::ReadOnly)) {
			QMessageBox::critical(this, tr("Error"), errmsg);
			return;
		}
		
		QByteArray ba = file.readAll();
		if (ba.size() != 0x138) {
			QMessageBox::critical(this, tr("Error"), errmsg2);
			return;
		}

		Colosseum::Pokemon importedPkm((u8*)ba.data());
		if (pkm == NULL) pkm = importedPkm.clone();
		else { *pkm = importedPkm; }
		parseData();
		lastPkmDirectory = fileInfo.canonicalPath();
	}
	else if (fileSize == 0xc4) {
		QFile file(fileName);
		if (!file.open(QIODevice::ReadOnly)) {
			QMessageBox::critical(this, tr("Error"), errmsg);
			return;
		}
		
		QByteArray ba = file.readAll();
		if (ba.size() != 0xc4) {
			QMessageBox::critical(this, tr("Error"), errmsg2);
			return;
		}

		XD::Pokemon importedPkm((const u8*)ba.data());
		if (pkm == NULL) pkm = importedPkm.clone();
		else { *pkm = importedPkm; }
		parseData();
		lastPkmDirectory = fileInfo.canonicalPath();
	}
	else {
		QMessageBox::critical(this, tr("Error"), tr("Invalid file size."));
	}
}

void PokemonDisplayWidget::openExportPkmDialog(void) {
	const QString errmsg = tr("Could not write to file.");
	const QString errmsg2 = tr("An error occured while writing to the specified Pok\xc3\xa9mon file.");

	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Pok\xc3\xa9mon file"), lastPkmDirectory, selectFilters());
	if (fileName.isEmpty()) return;
	
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly)) {
		QMessageBox::critical(this, tr("Error"), errmsg);
		return;
	}

	QString selectedExt = fileName.section(".", -1);

	
	GC::Pokemon* exportedPkm = pkm;
	bool created = false;
	
	if ((selectedExt == "colopkm") && !LIBPKMGC_IS_COLOSSEUM(Pokemon, pkm)) {
		exportedPkm = new Colosseum::Pokemon(*(XD::Pokemon*)pkm);
		created = true;
	}
	else if ((selectedExt == "xdpkm") && !LIBPKMGC_IS_XD(Pokemon, pkm)) {
		exportedPkm = new XD::Pokemon(*(Colosseum::Pokemon*)pkm);
		created = true;
	}

	exportedPkm->save();

	if (file.write((const char*)exportedPkm->data, exportedPkm->fixedSize) != (qint64)exportedPkm->fixedSize)
		QMessageBox::critical(this, tr("Error"), errmsg2);
	else
		lastPkmDirectory = QFileInfo(fileName).canonicalPath();
	
	if (created) delete exportedPkm;

}

}