#ifndef _PKMGCSAVEEDITOR_PLAYER_UI
#define _PKMGCSAVEEDITOR_PLAYER_UI

#include <GCUIs/BagEditor.h>
#include <Core/TrainerInfoLayout.h>
#include <GCUIs/PokemonDisplayWidget.h>
#include <Core/DataUI.h>
#include <QGroupBox>


namespace GCUIs{

class PlayerUI : public DataUI{
	Q_OBJECT
public:
	PlayerUI(LibPkmGC::GC::PlayerData* inPlayer = NULL, QWidget *parent = NULL, Qt::WindowFlags f = Qt::Window);
	~PlayerUI(void);
	void parseData(void);

	LibPkmGC::GC::PlayerData *player;

	void saveChanges(void);
	void cancelChanges(void);

public slots:
	void pkmDeletionHandler(LibPkmGC::PokemonStorageInfo const& location);

protected:
	void initWidget(void);
private:

	QTabWidget* tabs;

	QWidget* generalTab;
	QVBoxLayout* generalTabLayout;
	QGroupBox* trainerInfoBox;
	TrainerInfoLayout* trainerInfoFld;

	QGroupBox* currenciesBox;
	QFormLayout* currenciesLayout;
	UnsignedSpinbox<32> *moneyFld, *pkCouponsFld;

	BagEditor* bagTab;
	
	QWidget* partyTab;
	QVBoxLayout* partyTabLayout;
	PokemonDisplayWidget* pkmFlds[6];
};

}

#endif