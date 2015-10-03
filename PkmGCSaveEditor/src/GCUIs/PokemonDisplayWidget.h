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

#ifndef _PKMGCSAVEEDITOR_POKEMON_DISPLAY_WIDGET_H
#define _PKMGCSAVEEDITOR_POKEMON_DISPLAY_WIDGET_H

#include <GCUIs/PokemonUI.h>
#include <QPlainTextEdit>

namespace GCUIs {

class PokemonBase64InputDialog : public QDialog {
	Q_OBJECT
public:
	static QStringList formats(void);
	PokemonBase64InputDialog(QWidget* parent = NULL);

	QByteArray const& result(void);

private:
	bool valid;
	QByteArray data;
	QFormLayout* inputLayout;
	QVBoxLayout* mainLayout;
	QLabel* format;
	QPlainTextEdit* contents;
	QDialogButtonBox* buttons;
public slots:
	void accept(void);
	void update(void);
};

class PokemonBase64OutputDialog : public QDialog {
	Q_OBJECT
public:
	PokemonBase64OutputDialog(LibPkmGC::GC::Pokemon* inPkm, QWidget* parent = NULL);

	LibPkmGC::GC::Pokemon* pkm;

private:
	QFormLayout* outputLayout;
	QVBoxLayout* mainLayout;
	QComboBox* format;
	QPlainTextEdit* contents;
	QDialogButtonBox* buttons;
public slots:
	void update(void);
};

class PokemonDisplayWidget : public QWidget, IDataUI {
	Q_OBJECT
public:
	PokemonDisplayWidget(LibPkmGC::GC::Pokemon* inPkm = NULL, LibPkmGC::PokemonStorageInfo const& inLocation = LibPkmGC::emptyStorageInfo,
		QWidget* parent = NULL);
	~PokemonDisplayWidget(void);

	LibPkmGC::GC::Pokemon *pkm, *pkmBackup;
	LibPkmGC::PokemonStorageInfo location;

	void parseData(void);
	void saveChanges(void);
	void cancelChanges(void);

protected:
	void initWidget(void);
signals:
	void pkmUpdated(LibPkmGC::GC::Pokemon* pkm, LibPkmGC::PokemonStorageInfo location);
	void pkmDeleted(LibPkmGC::PokemonStorageInfo const& location);

public slots:
	void updatePkmNameAndSummary(void);
	void openImportPkmFileDialog(void);
	void openImportBase64Dialog(void);
	void openExportPkmFileDialog(void);
	void openExportBase64Dialog(void);
	void deletePkm(void);
	void openPkmUI(void);

private:
	QHBoxLayout* mainLayout;
	QLabel* nameFld;
	QLabel* summary;
	QHBoxLayout *buttonsLayout;
	QPushButton *editButton;
	QPushButton *deleteButton;
	QPushButton *importButton;
	QPushButton *exportButton;

	QMenu* importMenu;
	QAction *importFileAction, *importBase64Action;
	QMenu* exportMenu;
	QAction *exportFileAction, *exportBase64Action;


	QString selectFilters(bool op = true);

	template<typename P>
	void importPkmFromData(QByteArray const& ba, size_t sz = P::size) {
		P* importedPkm = NULL;
		if (sz != 80)
			importedPkm = new P((const u8*)ba.constData());
		else {
			GBA::Pokemon* pk2 = GBA::Pokemon::load80((const u8*)ba.constData());
			importedPkm = new P(*pk2);
			delete pk2;
		}

		if (pkm == NULL) {
			if (LIBPKMGC_IS_XD(Pokemon, importedPkm) || (currentSaveSlot != NULL && LIBPKMGC_IS_XD(SaveEditing::SaveSlot, currentSaveSlot)))
				pkm = new XD::Pokemon(*importedPkm);
			else
				pkm = new Colosseum::Pokemon(*importedPkm);
		}
		else *pkm = *importedPkm;

		if (P::size == 100 && currentSaveSlot != NULL)
			pkm->version.currentRegion = currentSaveSlot->gameConfig->version.currentRegion;

		delete importedPkm;
		parseData();
	}

	template<typename P>
	void readExpected(QString const& fileName, size_t sz = P::size) {
		const QString errmsg = tr("Could not open file.");
		const QString errmsg2 = tr("An error occured while reading the specified Pok\xc3\xa9mon file.");
		QFile file(fileName);
		if (!file.open(QIODevice::ReadOnly)) {
			QMessageBox::critical(this, tr("Error"), errmsg);
			return;
		}

		QByteArray ba = file.readAll();
		if (ba.size() != sz) {
			QMessageBox::critical(this, tr("Error"), errmsg2);
			return;
		}

		importPkmFromData<P>(ba, sz);
		lastPkmDirectory = QFileInfo(fileName).canonicalPath();
	}


};

}

#endif 