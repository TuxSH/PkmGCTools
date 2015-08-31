
#ifndef _PKMGCSAVEEDITOR_POKEMON_DISPLAY_WIDGET_H
#define _PKMGCSAVEEDITOR_POKEMON_DISPLAY_WIDGET_H

#include <GCUIs/PokemonUI.h>

namespace GCUIs {

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
	void openImportPkmDialog(void);
	void openExportPkmDialog(void);
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

	QString selectFilters(void);

};

}

#endif 