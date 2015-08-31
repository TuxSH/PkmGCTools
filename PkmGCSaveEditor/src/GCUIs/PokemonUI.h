#ifndef _PKMGCSAVEEDITOR_POKEMON_UI_H
#define _PKMGCSAVEEDITOR_POKEMON_UI_H

#include <Core/DataUI.h>
#include <QScopedPointer>
#include <QLineEdit>
#include <QCheckBox>
#include <QGroupBox>
#include <QTabWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QStackedWidget>
#include <Core/VersionInfoLayout.h>
#include <Core/TrainerInfoLayout.h>
#include <Core/ItemComboBox.h>
#include <QPushButton>


namespace GCUIs {

class PokemonStatLayout : public QHBoxLayout {
	Q_OBJECT
public:
	PokemonStatLayout(LibPkmGC::u8 inIV = 0, LibPkmGC::u8 inEV = 0, LibPkmGC::u16 inStat = 0);

	UnsignedSpinbox<5> *IVFld;
	UnsignedSpinbox<8> *EVFld;
	UnsignedSpinbox<16> *statFld;

public slots:
	void IVOrEVChangedEmitter(void);
signals:
	void IVOrEVChanged(void);
};

class PokemonMoveLayout : public QHBoxLayout {
	Q_OBJECT
public:
	PokemonMoveLayout(LibPkmGC::PokemonMove const& inMove = LibPkmGC::PokemonMove());

	LibPkmGC::PokemonMove move(void) const;
	void setMove(LibPkmGC::PokemonMove const& inMove);

private:

	QComboBox *moveNameFld;
	UnsignedSpinbox<7> *currentPPsFld;
	QLabel *maxPPsFld;
	UnsignedSpinbox<2> *nbPPUpsUsedFld;
	QLabel* nbPPUpsUsedText;


public slots:
	void updateFields(void);

};

class PokemonUI : public DataUI {
	Q_OBJECT
public:
	PokemonUI(LibPkmGC::GC::Pokemon* inPkm = NULL, LibPkmGC::PokemonStorageInfo const& inLocation = LibPkmGC::emptyStorageInfo, QWidget* parent = NULL,
		Qt::WindowFlags f = Qt::Window);
	

	static QStringList statusNames(void);

	void parseData(void);
	void saveChanges(void);

	static QString getShortPkmAttributeText(LibPkmGC::PokemonSpeciesIndex species, LibPkmGC::u32 PID, LibPkmGC::u16 TID, LibPkmGC::u16 SID);
	static QString getLongPkmAttributeText(LibPkmGC::PokemonSpeciesIndex species, LibPkmGC::u32 PID, LibPkmGC::u16 TID, LibPkmGC::u16 SID);
	QString getShortPkmAttributeText(void);
	QString getLongPkmAttributeText(void);

	LibPkmGC::GC::Pokemon* pkm;
	
	LibPkmGC::PokemonStorageInfo location;
protected:
	virtual void initWidget(void);

private:
	QTabWidget* tabs;

	QWidget *generalTab, *metTab;
	QFormLayout *generalTabLayout;
	QVBoxLayout *metTabLayout;

	// "General" tab:
	QComboBox *speciesFld;
	QHBoxLayout* nameLayout;
	QLineEdit* nameFld;
	QPushButton *resetNameButton;

	UnsignedSpinbox<32>* PIDFld;
	QLabel *attributesFld;

	QComboBox* abilityFld;

	QHBoxLayout* experienceLevelAndSyncLayout;
	QHBoxLayout* levelAndSyncLayout;
	UnsignedSpinbox<32>* experienceFld;
	UnsignedSpinbox<7>* levelFld;
	QCheckBox* syncLevelAndExpFldsCheckBox;

	ItemComboBox* heldItemFld;
	UnsignedSpinbox<8>* happinessFld;
	UnsignedSpinbox<8>* pkrsStatusFld;

	QComboBox* statusFld;

	QGridLayout *flagsLayout;
	QButtonGroup *flagsButtonGroup;
	QCheckBox *eggFlagCheckBox, *secondAbilityFlagCheckBox, *invalidPokemonCheckBox;
	QCheckBox *notTradableInGameFlagCheckBox, *unknownFlagCheckBox, *caughtFlagCheckBox;

	QHBoxLayout* markingsLayout;
	QButtonGroup* markingsButtonGroup;
	QCheckBox *circleMarkingCheckBox, *squareMarkingCheckBox, *triangleMarkingCheckBox, *heartMarkingCheckBox;


	// "Met" tab:
	QGroupBox* coreCaptureInfoBox;
	QFormLayout* coreCaptureInfoLayout;
	ItemComboBox* ballCaughtWithFld;
	UnsignedSpinbox<8>* locationCaughtFld;

	QGroupBox* OTBox;
	TrainerInfoLayout* OTField;

	QGroupBox* versionBox;
	VersionInfoLayout* versionFld;

	QHBoxLayout* metActionsLayout;
	QPushButton *copyInfoFromSaveButton, *generateShinyIDsButton;

	// "Stats" tab:
	QWidget* statsTab;
	QVBoxLayout* statsTabLayout;
	QTabWidget* statsSubTabs;
	QWidget* mainStatsTab;
	QVBoxLayout* mainStatsLayout;
	QCheckBox* autoUpdateMainStatsCheckBox;
	QHBoxLayout *mainStatsTitleLayout;
	QFormLayout* mainStatsFormLayout;
	UnsignedSpinbox<16>* currentHPFld;
	PokemonStatLayout *mainStatsFlds[6];

	QWidget* contestStatsTab;
	QFormLayout* contestStatsLayout;
	UnsignedSpinbox<8>* contestStatsLusterFld;
	UnsignedSpinbox<8>* contestStatsFlds[5];

	// "Moves" tab:
	QWidget* movesTab;
	QVBoxLayout* movesTabLayout;
	//QHBoxLayout* movesTitleLayout;
	PokemonMoveLayout* moveLayouts[4];

	// "Ribbons" tab:
	QWidget* ribbonsTab;
	QVBoxLayout *ribbonsTabLayout;
	QGroupBox *contestAchievementsBox;
	QFormLayout *contestAchievementsLayout;
	QComboBox *contestTypeSelector;
	QStackedWidget* contestAchievementLevelFldsStack;
	QComboBox* contestAchievementFlds[5];
	QGroupBox *specialRibbonsBox;
	QGridLayout *specialRibbonsLayout;
	QButtonGroup *specialRibbonsFldGroup;
	QCheckBox *specialRibbonsFlds[12];


public slots:
	void updateMainStats(void);
	void updatePkmAttributes(void);
	void updateAbilityList(void);
	void updateExperienceFromLevel(void);
	void updateLevelFromExperience(void);
	void speciesChangeHandler(void);
	void PIDChangeHandler(void);

	void updateFlags(void);
	void flagsStateChangeHandler(void);

	void autoUpdateStatsStateChangeHanler(void);

	void versionChangeHandler(void);

	void resetName(void);
	void copyInfoFromSave(void);
	void generateShinyIDs(void);
};

}

#endif