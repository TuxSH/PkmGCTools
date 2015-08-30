#ifndef _PKMGCSAVEEDITOR_POKEMON_BOX_EDITOR_H
#define _PKMGCSAVEEDITOR_POKEMON_BOX_EDITOR_H
#include <GCUIs/PokemonDisplayWidget.h>

namespace GCUIs {

class PokemonBoxEditor : public QWidget, public IDataUI {
	Q_OBJECT
public:
	PokemonBoxEditor(LibPkmGC::GC::PokemonBox* inBox = NULL, size_t inBoxNb = 0, QWidget* parent = NULL);
	~PokemonBoxEditor(void);

	void parseData(void);
	LibPkmGC::GC::PokemonBox* box;
	size_t boxNb;

	void saveChanges(void);
	void cancelChanges(void);
	QString currentBoxName(void) const;

signals:
	void nameChanged(size_t nb, QString const& newName);
public slots:
	//void pkmDeletionHandler(LibPkmGC::PokemonStorageInfo const & location);
	void nameChangedEmitter(QString const& newName);
protected:
	void initWidget(void);
private:
	bool isXD;
//	LibPkmGC::GC::PokemonBox* boxBackup;
	
	QVBoxLayout* mainLayout;
	QFormLayout* nameLayout;
	QLineEdit* nameFld;
	QTabWidget *tabs;
	QWidget *pages[5];
	QVBoxLayout *pageLayouts[5];
	PokemonDisplayWidget* pkmFlds[30];
};

}

#endif