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

#ifndef _PKMGCSAVEEDITOR_POKEMON_UI_H
#define _PKMGCSAVEEDITOR_POKEMON_UI_H

#include <Core/DataUI.h>
#include <QScopedPointer>
#include <QLineEdit>
#include <QCheckBox>
#include <QGroupBox>
#include <QTabWidget>
#include <QHBoxLayout>
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

	void setHiddenPower(TypeIndex t, LibPkmGC::u8 p);

private:
	AutocompletingComboBox* moveNameFld;
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
	static QStringList ribbonNames(void);
	static QString ribbonHasNeverBeenMadeAvailableStr(void);
	static QStringList invalidPkmStrs(void);

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

	QWidget *generalTab;
	QWidget *metTab;
	QVBoxLayout *metTabLayout;

	// "General" tab:
	QVBoxLayout *generalTabLayout;
	QTabWidget *generalSubTabs;

	QWidget *generalCoreSubTab, *generalStatusSubTab;
	QFormLayout *generalCoreSubTabLayout, *generalStatusSubTabLayout;

	AutocompletingComboBox *speciesFld;
	QHBoxLayout* nameLayout;
	QLineEdit* nameFld;
	QPushButton *resetNameButton;

	QHBoxLayout* PIDLayout;
	UnsignedSpinbox<32>* PIDFld;
	QButtonGroup* PIDButtonGroup;
	QRadioButton *hexPIDButton, *decPIDButton;
	QLabel *attributesFld;

	QComboBox* abilityFld;

	QHBoxLayout* experienceLevelAndSyncLayout;
	QHBoxLayout* levelAndSyncLayout;
	UnsignedSpinbox<32>* experienceFld;
	UnsignedSpinbox<7>* levelFld;
	QCheckBox* syncLevelAndExpFldsCheckBox;

	ItemComboBox* heldItemFld;
	UnsignedSpinbox<8>* friendshipFld;
	QHBoxLayout* pokerusStatusLayout;
	UnsignedSpinbox<3>* pokerusDaysRemainingFld;
	UnsignedSpinbox<4>* pokerusStrainFld;

	QComboBox* statusFld;
	QSpinBox* turnsOfBadPoisonFld;
	QSpinBox* turnsOfSleepRemainingFld;
	QSpinBox* partyPrksDaysRemainingFld;


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
	UnsignedSpinbox<8>* locationCaughtFld;
	ItemComboBox* ballCaughtWithFld;
	UnsignedSpinbox<7>* levelMetFld;
	QCheckBox* obedientFld;

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

	LibPkmGC::PokemonSpeciesIndex oldSpecies;
public slots:
	void updateMainStats(void);
	void updatePIDDisplay(int i);
	void updatePkmAttributes(void);
	void updateAbilityList(void);
	void updateExperienceFromLevel(bool proportionally = false);
	void updateLevelFromExperience(void);
	void speciesChangeHandler(void);
	void PIDChangeHandler(void);
	void updatePokerusDaysRemaining(void);
	void statusChangeHandler(void);

	void updateFlags(void);
	void flagsStateChangeHandler(void);

	void updateHiddenPowerText(void);
	void autoUpdateStatsStateChangeHandler(void);

	void versionChangeHandler(void);

	void resetName(void);
	void copyInfoFromSave(void);
	void generateShinyIDs(void);
};

}

#endif