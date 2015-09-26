#include <GCUIs/PokemonUI.h>
#include <QMessageBox>

using namespace LibPkmGC; using namespace Localization; using namespace Base;


namespace GCUIs {

PokemonMoveLayout::PokemonMoveLayout(PokemonMove const& inMove) : QHBoxLayout(){
	LanguageIndex lg = generateDumpedNamesLanguage();
	moveNameFld = new QComboBox;
	currentPPsFld = new UnsignedSpinbox<7>;
	maxPPsFld = new QLabel(tr("(max. %n)", "", 0));
	nbPPUpsUsedFld = new UnsignedSpinbox<2>;
	nbPPUpsUsedText = new QLabel(tr("PP Up(s) used"));

	currentPPsFld->setRange(0, 64);

	QHBoxLayout* w1 = new QHBoxLayout;
	w1->addWidget(moveNameFld);
	w1->addWidget(currentPPsFld);
	w1->addWidget(maxPPsFld);

	QHBoxLayout* w2 = new QHBoxLayout;
	w2->addWidget(nbPPUpsUsedFld);
	w2->addWidget(nbPPUpsUsedText);
	w2->setAlignment(Qt::AlignRight);

	this->addLayout(w1, 3);
	this->addLayout(w2, 1);

	for (size_t i = 0; i <= (size_t)PsychoBoost; ++i)
		moveNameFld->addItem(getPokemonMoveName(lg, (PokemonMoveIndex)i));

	connect(moveNameFld, SIGNAL(currentIndexChanged(int)), this, SLOT(updateFields()));
	connect(nbPPUpsUsedFld, SIGNAL(valueChanged(int)), this, SLOT(updateFields()));

	setMove(inMove);
}

PokemonMove PokemonMoveLayout::move(void) const {
	PokemonMove _move = { (PokemonMoveIndex)moveNameFld->currentIndex(), (u8)currentPPsFld->value(), (u8)nbPPUpsUsedFld->value() };
	return _move;
}

void PokemonMoveLayout::setMove(PokemonMove const& inMove) {
	moveNameFld->disconnect(SIGNAL(currentIndexChanged(int)), this);
	nbPPUpsUsedFld->disconnect(SIGNAL(valueChanged(int)), this);

	currentPPsFld->setUnsignedRange(0, 64);
	currentPPsFld->setUnsignedValue(inMove.currentPPs);
	moveNameFld->setCurrentIndex((inMove.move > PsychoBoost) ? 0 : (int) inMove.move);
	nbPPUpsUsedFld->setUnsignedValue(inMove.nbPPUpsUsed);

	connect(moveNameFld, SIGNAL(currentIndexChanged(int)), this, SLOT(updateFields()));
	connect(nbPPUpsUsedFld, SIGNAL(valueChanged(int)), this, SLOT(updateFields()));

	updateFields();
}

void PokemonMoveLayout::updateFields(void) {
	PokemonMove _move = move();
	u8 maxPPs = _move.calculateMaxPP();
	maxPPsFld->setText(tr("(max. %n)", "", maxPPs));
	currentPPsFld->setRange(0, (int)maxPPs);
}

PokemonStatLayout::PokemonStatLayout(u8 inIV, u8 inEV, u16 inStat) : QHBoxLayout(){
	IVFld = new UnsignedSpinbox<5>;
	EVFld = new UnsignedSpinbox<8>;
	statFld = new UnsignedSpinbox<16>;

	IVFld->setUnsignedValue(inIV);
	EVFld->setUnsignedValue(inEV);
	statFld->setUnsignedValue(inStat);
	this->addWidget(IVFld);
	this->addWidget(EVFld);
	this->addWidget(statFld);
	connect(IVFld, SIGNAL(valueChanged(int)), this, SLOT(IVOrEVChangedEmitter()));
	connect(EVFld, SIGNAL(valueChanged(int)), this, SLOT(IVOrEVChangedEmitter()));
}

void PokemonStatLayout::IVOrEVChangedEmitter(void) {
	emit IVOrEVChanged();
}


PokemonUI::PokemonUI(GC::Pokemon * inPkm,
					 PokemonStorageInfo const& inLocation, QWidget * parent, Qt::WindowFlags f) : DataUI(parent,f), pkm(inPkm), location(inLocation){
	init();
}

QStringList PokemonUI::statusNames(void) {
	return QStringList() << tr("None", "Status") << tr("Poisoned") << tr("Badly poisoned") <<
		tr("Paralyzed") << tr("Burnt") << tr("Frozen") << tr("Asleep");
}

void PokemonUI::initWidget(void){
	const QStringList contestStatNames = QStringList() << tr("Coolness") << tr("Beauty") << tr("Cuteness")
		<< tr("Cleverness") << tr("Toughness");

	const QStringList contestAchivementLevelNames = QStringList() << tr("None", "Contest") << tr("Normal", "Contest")
		<< tr("Super", "Contest") << tr("Hyper", "Contest")
		<< tr("Master", "Contest");

	const QStringList statNames = QStringList() << tr("HP") << tr("Attack") << tr("Defense") <<
		tr("S. Attack") << tr("S. Defense") << tr("Speed");

	const QStringList srNames = QStringList() << tr("Champion") << tr("Winning") << tr("Victory") << tr("Artist") <<
		tr("Effort") << tr("Marine") << tr("Land") << tr("Sky") <<
		tr("Country") << tr("National") << tr("Earth") << tr("World");

	LanguageIndex lg = generateDumpedNamesLanguage();

	oldSpecies = (PokemonSpeciesIndex)-1; // invalid
	mainLayout = new QVBoxLayout;
	tabs = new QTabWidget;

	generalTab = new QWidget;
	metTab = new QWidget;
	statsTab = new QWidget;
	movesTab = new QWidget;
	ribbonsTab = new QWidget;
	
	generalTabLayout = new QVBoxLayout;
	metTabLayout = new QVBoxLayout;
	statsTabLayout = new QVBoxLayout;
	movesTabLayout = new QVBoxLayout;
	ribbonsTabLayout = new QVBoxLayout;
	
	//-----------------------------"General" tab:-----------------------------------------------
	generalSubTabs = new QTabWidget;
	generalCoreSubTab = new QWidget;
	generalCoreSubTabLayout = new QFormLayout;

	generalStatusSubTab = new QWidget;
	generalStatusSubTabLayout = new QFormLayout;

	speciesFld = new QComboBox;
	nameLayout = new QHBoxLayout;
	nameFld = new QLineEdit;
	resetNameButton = new QPushButton(tr("Reset"));
	PIDFld = new UnsignedSpinbox<32>;
	attributesFld = new QLabel;
	abilityFld = new QComboBox;
	experienceLevelAndSyncLayout = new QHBoxLayout;
	levelAndSyncLayout = new QHBoxLayout;
	experienceFld = new UnsignedSpinbox<32>;
	levelFld = new UnsignedSpinbox<7>;
	syncLevelAndExpFldsCheckBox = new QCheckBox;
	
	heldItemFld = new ItemComboBox;
	happinessFld = new UnsignedSpinbox<8>;
	pkrsStatusLayout = new QHBoxLayout;
	pkrsDaysRemainingFld = new UnsignedSpinbox<3>;
	pkrsStrainFld = new UnsignedSpinbox<4>;
	flagsLayout = new QGridLayout;
	flagsButtonGroup = new QButtonGroup;
	markingsLayout = new QHBoxLayout;
	markingsButtonGroup = new QButtonGroup;


	for (size_t i = 0; i < 387; ++i)
		speciesFld->addItem(Localization::getPokemonSpeciesNameByPkdxIndex(lg, i));

	nameFld->setMaxLength(10);
	nameLayout->addWidget(nameFld);
	nameLayout->addWidget(resetNameButton);
	abilityFld->addItem(Localization::getPokemonAbilityName(lg, NoAbility));
	abilityFld->setDisabled(true);

	levelFld->setRange(1, 100);
	syncLevelAndExpFldsCheckBox->setChecked(true);

	pkrsDaysRemainingFld->setUnsignedRange(0, 4);


	experienceLevelAndSyncLayout->addWidget(experienceFld,2);
	levelAndSyncLayout->addWidget(levelFld,1);
	levelAndSyncLayout->addWidget(syncLevelAndExpFldsCheckBox);
	levelAndSyncLayout->setAlignment(Qt::AlignRight);
	experienceLevelAndSyncLayout->addLayout(levelAndSyncLayout);

	pkrsStatusLayout->addWidget(pkrsDaysRemainingFld);
	pkrsStatusLayout->addWidget(pkrsStrainFld);

	eggFlagCheckBox = new QCheckBox(tr("Egg")); secondAbilityFlagCheckBox = new QCheckBox(tr("Second ability")); 
	invalidPokemonCheckBox = new QCheckBox(tr("Invalid Pok\xc3\xa9mon"));
	notTradableInGameFlagCheckBox = new QCheckBox(tr("Not tradable in-game")); unknownFlagCheckBox = new QCheckBox(tr("Unknown"));
	caughtFlagCheckBox = new QCheckBox(tr("Caught"));

	QCheckBox* g1[] = { eggFlagCheckBox, secondAbilityFlagCheckBox, invalidPokemonCheckBox,
						notTradableInGameFlagCheckBox, unknownFlagCheckBox, caughtFlagCheckBox };

	flagsButtonGroup->setExclusive(false);
	for (int i = 0; i < 6; ++i) {
		flagsButtonGroup->addButton(g1[i], i);
		flagsLayout->addWidget(g1[i], i / 3, i % 3);
		connect(g1[i], SIGNAL(stateChanged(int)), this, SLOT(flagsStateChangeHandler()));
	}


	circleMarkingCheckBox = new QCheckBox("\xe2\x97\x8f"); squareMarkingCheckBox = new QCheckBox("\xe2\x96\xa0");
	triangleMarkingCheckBox = new QCheckBox("\xe2\x96\xb2"); heartMarkingCheckBox = new QCheckBox("\xe2\x99\xa5");

	QCheckBox* g2[] = { circleMarkingCheckBox, squareMarkingCheckBox, triangleMarkingCheckBox, heartMarkingCheckBox };

	markingsButtonGroup->setExclusive(false);

	for (int i = 0; i < 4; ++i) {
		markingsButtonGroup->addButton(g2[i], i);
		markingsLayout->addWidget(g2[i]);
	}

	generalCoreSubTabLayout->addRow(tr("Species"), speciesFld);
	generalCoreSubTabLayout->addRow(tr("Name or nickname"), nameLayout);
	generalCoreSubTabLayout->addRow(tr("PID"), PIDFld);
	generalCoreSubTabLayout->addRow(tr("Attributes"), attributesFld);
	generalCoreSubTabLayout->addRow(tr("Ability"), abilityFld);
	generalCoreSubTabLayout->addRow(tr("Experience and level"), experienceLevelAndSyncLayout);
	generalCoreSubTabLayout->addRow(tr("Held item"), heldItemFld);
	generalCoreSubTabLayout->addRow(tr("Happiness"), happinessFld);
	generalCoreSubTabLayout->addRow(tr("Pok\xc3\xa9rus (days remaing and strain)"), pkrsStatusLayout);
	generalCoreSubTabLayout->addRow(tr("Flags"), flagsLayout);
	generalCoreSubTabLayout->addRow(tr("Markings"), markingsLayout);


	statusFld = new QComboBox;
	partyPrksDaysRemainingFld = new QSpinBox;
	turnsOfBadPoisonFld = new QSpinBox;
	turnsOfSleepRemainingFld = new QSpinBox;

	statusFld->addItems(statusNames());

	partyPrksDaysRemainingFld->setRange(-1, 4);
	turnsOfBadPoisonFld->setRange(0, 15);
	turnsOfSleepRemainingFld->setRange(0, 7);

	generalStatusSubTabLayout->addRow(tr("Status"), statusFld);
	generalStatusSubTabLayout->addRow(tr("Pok\xc3\xa9rus days remaining"), partyPrksDaysRemainingFld);
	generalStatusSubTabLayout->addRow(tr("Turns of sleep remaining"), turnsOfSleepRemainingFld);
	generalStatusSubTabLayout->addRow(tr("Turns of bad poison"), turnsOfBadPoisonFld);

	generalCoreSubTab->setLayout(generalCoreSubTabLayout);
	generalStatusSubTab->setLayout(generalStatusSubTabLayout);

	generalSubTabs->addTab(generalCoreSubTab, tr("Core"));
	generalSubTabs->addTab(generalStatusSubTab, tr("Status"));

	generalTabLayout->addWidget(generalSubTabs);
	generalTab->setLayout(generalTabLayout);
	//----------------------------------------------------------------------------------------


	// ---------------------------------"Met" tab:---------------------------------------------

	coreCaptureInfoBox = new QGroupBox(tr("Core information"));
	OTBox = new QGroupBox(tr("Original trainer"));
	versionBox = new QGroupBox(tr("Game version"));

	coreCaptureInfoLayout = new QFormLayout;
	OTField = new TrainerInfoLayout;
	versionFld = new VersionInfoLayout;

	locationCaughtFld = new UnsignedSpinbox<8>;
	levelMetFld = new UnsignedSpinbox<7>;
	obedientFld = new QCheckBox;
	ballCaughtWithFld = new ItemComboBox(POKEBALLS_ALLOWED | EMPTY_ITEM_FORBIDDEN);

	metActionsLayout = new QHBoxLayout;
	copyInfoFromSaveButton = new QPushButton(tr("Copy info from save"));
	generateShinyIDsButton = new QPushButton(tr("Generate shiny IDs"));

	levelMetFld->setUnsignedRange(1, 100);

	coreCaptureInfoLayout->addRow(tr("Location caught"), locationCaughtFld);
	coreCaptureInfoLayout->addRow(tr("Level met"), levelMetFld);
	coreCaptureInfoLayout->addRow(tr("Fateful encounter (obedient)"), obedientFld);
	coreCaptureInfoLayout->addRow(tr("Ball caught with"), ballCaughtWithFld);

	coreCaptureInfoLayout->labelForField(obedientFld)->setToolTip(tr("Mew and Deoxys need this field to be checked so they can obey.\n"
		"Pok\xc3\xa9mon caught in XD always have this field checked."));
	coreCaptureInfoBox->setLayout(coreCaptureInfoLayout);
	OTBox->setLayout(OTField);
	versionBox->setLayout(versionFld);
	
	metActionsLayout->addWidget(copyInfoFromSaveButton);
	metActionsLayout->addWidget(generateShinyIDsButton);

	metTabLayout->addWidget(coreCaptureInfoBox);
	metTabLayout->addWidget(OTBox);
	metTabLayout->addWidget(versionBox);
	metTabLayout->addLayout(metActionsLayout);


	//----------------------------------------------------------------------------------------

	// --------------------------------"Stats" tab:--------------------------------------------


	statsSubTabs = new QTabWidget;


	mainStatsTab = new QWidget;

	mainStatsLayout = new QVBoxLayout;
	mainStatsTitleLayout = new QHBoxLayout;
	mainStatsFormLayout = new QFormLayout;

	mainStatsTitleLayout->addWidget(new QLabel(tr("IV")));
	mainStatsTitleLayout->addWidget(new QLabel(tr("EV")));
	mainStatsTitleLayout->addWidget(new QLabel(tr("Stat")));

	currentHPFld = new UnsignedSpinbox<16>;
	mainStatsFormLayout->addRow(tr("Current HP"), currentHPFld);
	mainStatsFormLayout->addRow("", mainStatsTitleLayout);
	for (size_t i = 0; i < 6; ++i) {
		mainStatsFlds[i] = new PokemonStatLayout;
		mainStatsFormLayout->addRow(statNames[i], mainStatsFlds[i]);
		connect(mainStatsFlds[i], SIGNAL(IVOrEVChanged()), this, SLOT(updateMainStats()));
	}
	autoUpdateMainStatsCheckBox = new QCheckBox(tr("Update stats automatically"));
	autoUpdateMainStatsCheckBox->setChecked(true);

	mainStatsLayout->addLayout(mainStatsFormLayout);
	mainStatsLayout->addWidget(autoUpdateMainStatsCheckBox);
	mainStatsTab->setLayout(mainStatsLayout);


	contestStatsTab = new QWidget;
	contestStatsLayout = new QFormLayout;

	contestStatsLusterFld = new UnsignedSpinbox<8>;
	contestStatsLayout->addRow(tr("Luster"), contestStatsLusterFld);
	for (size_t i = 0; i < 5; ++i) {
		contestStatsFlds[i] = new UnsignedSpinbox<8>;
		contestStatsLayout->addRow(contestStatNames[i], contestStatsFlds[i]);
	}
	contestStatsTab->setLayout(contestStatsLayout);

	statsSubTabs->addTab(mainStatsTab, tr("Main stats"));
	statsSubTabs->addTab(contestStatsTab, tr("Contest stats"));

	statsTabLayout->addWidget(statsSubTabs);
	//----------------------------------------------------------------------------------------

	// --------------------------------"Moves" tab--------------------------------------------
	movesTabLayout->addStretch();

	for (size_t i = 0; i < 4; ++i) {
		moveLayouts[i] = new PokemonMoveLayout;
		movesTabLayout->addLayout(moveLayouts[i]);
	}

	movesTabLayout->addStretch();

	//----------------------------------------------------------------------------------------

	
	// -------------------------------"Ribbons" tab-------------------------------------------
	contestAchievementsBox = new QGroupBox(tr("Contest ribbons"));
	contestAchievementsLayout = new QFormLayout;
	contestTypeSelector = new QComboBox;
	contestAchievementLevelFldsStack = new QStackedWidget;

	for (size_t i = 0; i < 5; ++i) {
		contestAchievementFlds[i] = new QComboBox;
		contestAchievementFlds[i]->addItems(contestAchivementLevelNames);
		contestAchievementLevelFldsStack->addWidget(contestAchievementFlds[i]);
	}

	contestTypeSelector->addItems(contestStatNames);

	contestAchievementsLayout->addRow(tr("Contest type"), contestTypeSelector);
	contestAchievementsLayout->addRow(tr("Achievement"), contestAchievementLevelFldsStack);
	
	contestAchievementsBox->setLayout(contestAchievementsLayout);

	specialRibbonsBox = new QGroupBox(tr("Special ribbons"));
	specialRibbonsLayout = new QGridLayout;
	specialRibbonsFldGroup = new QButtonGroup;
	specialRibbonsFldGroup->setExclusive(false);
	
	for (size_t i = 0; i < 12; ++i) {
		specialRibbonsFlds[i] = new QCheckBox(srNames[i]);
		specialRibbonsFldGroup->addButton(specialRibbonsFlds[i], (int)i);
		specialRibbonsLayout->addWidget(specialRibbonsFlds[i], (int)(i % 4), (int)(i / 4));
	}

	specialRibbonsBox->setLayout(specialRibbonsLayout);

	ribbonsTabLayout->addWidget(contestAchievementsBox);
	ribbonsTabLayout->addWidget(specialRibbonsBox);
	//----------------------------------------------------------------------------------------



	
	metTab->setLayout(metTabLayout);
	statsTab->setLayout(statsTabLayout);
	movesTab->setLayout(movesTabLayout);
	ribbonsTab->setLayout(ribbonsTabLayout);

	tabs->addTab(generalTab, tr("General"));
	tabs->addTab(metTab, tr("Met/OT"));
	tabs->addTab(statsTab, tr("Stats"));
	tabs->addTab(movesTab, tr("Moves"));
	tabs->addTab(ribbonsTab, tr("Ribbons"));

	mainLayout->addWidget(tabs);
	DataUI::initWidget();

	connect(speciesFld, SIGNAL(currentIndexChanged(int)), this, SLOT(speciesChangeHandler()));
	connect(resetNameButton, SIGNAL(clicked()), this, SLOT(resetName()));
	connect(PIDFld, SIGNAL(valueChanged(int)), this, SLOT(PIDChangeHandler()));
	connect(abilityFld, SIGNAL(currentIndexChanged(int)), this, SLOT(updateFlags()));
	connect(experienceFld, SIGNAL(valueChanged(int)), this, SLOT(updateLevelFromExperience()));
	connect(levelFld, SIGNAL(valueChanged(int)), this, SLOT(updateExperienceFromLevel()));
	connect(statusFld, SIGNAL(currentIndexChanged(int)), SLOT(statusChangeHandler()));
	connect(pkrsStrainFld, SIGNAL(valueChanged(int)), this, SLOT(updatePkrsDaysRemaining()));
	connect(OTField, SIGNAL(TIDorSIDChanged()), this, SLOT(updatePkmAttributes()));
	connect(versionFld, SIGNAL(versionChanged()), this, SLOT(versionChangeHandler()));
	connect(copyInfoFromSaveButton, SIGNAL(clicked()), this, SLOT(copyInfoFromSave()));
	connect(generateShinyIDsButton, SIGNAL(clicked()), this, SLOT(generateShinyIDs()));
	connect(autoUpdateMainStatsCheckBox, SIGNAL(stateChanged(int)), this, SLOT(autoUpdateStatsStateChangeHandler()));
	connect(mainStatsFlds[0]->statFld, SIGNAL(valueChanged(int)), this, SLOT(updateMainStats()));
	connect(contestTypeSelector, SIGNAL(currentIndexChanged(int)), contestAchievementLevelFldsStack, SLOT(setCurrentIndex(int)));
}

void PokemonUI::parseData(void){
	if (pkm == NULL) return;
	copyInfoFromSaveButton->setDisabled(currentSaveSlot == NULL);

	// Blocking signals have a strange yet enormous cost on the main window when loading the save file

	autoUpdateMainStatsCheckBox->setChecked(false);
	syncLevelAndExpFldsCheckBox->setChecked(false);

	LanguageIndex lg = generateDumpedNamesLanguage();
	isXD = LIBPKMGC_IS_XD(Pokemon, pkm);


	if (isXD && (speciesFld->count() == 387))
		speciesFld->addItem(Localization::getPokemonSpeciesName(lg, Bonsly));
	else if (!isXD && (speciesFld->count() == 388))
		speciesFld->removeItem(387);
	heldItemFld->set(GIVABLE_ITEMS_ALLOWED, isXD);


	nameFld->setText(pkm->name->toUTF8());

	speciesFld->setCurrentIndex((int)Localization::pkmSpeciesIndexToNameIndex(pkm->species));
	if (pkm->species == Bonsly && !isXD) speciesFld->setCurrentIndex(0);
	PIDFld->setUnsignedValue(pkm->PID);


	u32 maxExperience = Pokemon::calculateExpFromLevel(nameIndexToPkmSpeciesIndex((size_t)speciesFld->currentIndex()), 100);
	experienceFld->setUnsignedRange(0, maxExperience);
	experienceFld->setUnsignedValue(pkm->experience);
	levelFld->setUnsignedValue(pkm->partyData.level);
	syncLevelAndExpFldsCheckBox->setChecked(true);


	heldItemFld->setCurrentItemIndex(pkm->heldItem);
	happinessFld->setUnsignedValue(pkm->happiness);


	statusFld->disconnect(SIGNAL(currentIndexChanged(int)), this);
	statusFld->setCurrentIndex((pkm->partyData.status == NoStatus) ? 0 : (int)pkm->partyData.status - 2);
	turnsOfBadPoisonFld->setValue(pkm->partyData.turnsOfBadPoison);
	turnsOfSleepRemainingFld->setValue(pkm->partyData.turnsOfSleepRemaining);
	statusChangeHandler();
	connect(statusFld, SIGNAL(currentIndexChanged(int)), SLOT(statusChangeHandler()));


	pkrsStrainFld->disconnect(SIGNAL(valueChanged(int)), this);
	pkrsStrainFld->setUnsignedValue(pkm->pkrsStatus & 0xf);
	pkrsDaysRemainingFld->setUnsignedValue(pkm->pkrsStatus >> 4);
	partyPrksDaysRemainingFld->setValue(pkm->pkrsStatus >> 4);
	updatePkrsDaysRemaining();

	connect(pkrsStrainFld, SIGNAL(valueChanged(int)), this, SLOT(updatePkrsDaysRemaining()));



	QCheckBox* g1[] = { eggFlagCheckBox, secondAbilityFlagCheckBox, invalidPokemonCheckBox,
						notTradableInGameFlagCheckBox, unknownFlagCheckBox, caughtFlagCheckBox };

	for (size_t i = 0; i < 3; ++i) {
		g1[i]->setChecked(pkm->pkmFlags[i]);
		g1[3 + i]->setVisible(isXD);
		if (isXD)
			g1[3 + i]->setChecked(static_cast<XD::Pokemon*>(pkm)->XDPkmFlags[i]);
	}

	circleMarkingCheckBox->setChecked(pkm->markings.circle);
	squareMarkingCheckBox->setChecked(pkm->markings.square);
	triangleMarkingCheckBox->setChecked(pkm->markings.triangle);
	heartMarkingCheckBox->setChecked(pkm->markings.heart);

	locationCaughtFld->setUnsignedValue(pkm->locationCaught);
	levelMetFld->setUnsignedValue(pkm->levelMet);
	ballCaughtWithFld->setCurrentItemIndex(pkm->ballCaughtWith);
	obedientFld->setChecked(pkm->obedient);
	OTField->set(pkm->OTName, pkm->TID, pkm->SID, pkm->OTGender);
	
	versionFld->disconnect(SIGNAL(versionChanged()), this);
	versionFld->setInfo(pkm->version);
	connect(versionFld, SIGNAL(versionChanged()), this, SLOT(versionChangeHandler()));

	for (size_t i = 0; i < 6; ++i) {
		PokemonStatLayout* l = mainStatsFlds[i];
		l->IVFld->setUnsignedValue(pkm->IVs[i]);
		l->EVFld->setUnsignedValue(pkm->EVs[i]);
		l->statFld->setUnsignedValue(pkm->partyData.stats[i]);
	}
	currentHPFld->setUnsignedValue(pkm->partyData.currentHP);


	for (size_t i = 0; i < 5; ++i)
		contestAchievementFlds[i]->setCurrentIndex((int)pkm->contestAchievements[i]);

	for (size_t i = 0; i < 12; ++i)
		specialRibbonsFlds[i]->setChecked(pkm->specialRibbons[i]);

	for (size_t i = 0; i < 4; ++i)
		moveLayouts[i]->setMove(pkm->moves[i]);

	autoUpdateMainStatsCheckBox->setChecked(true);
	autoUpdateStatsStateChangeHandler();
	versionChangeHandler();

	abilityFld->setCurrentIndex((pkm->hasSecondAbility()) ? 1 : 0);

	oldSpecies = pkm->species;
}

void PokemonUI::saveChanges(void){
	pkm->species = nameIndexToPkmSpeciesIndex(speciesFld->currentIndex());
	pkm->name->fromUTF8(nameFld->text().toUtf8().data());
	pkm->PID = PIDFld->unsignedValue();

	pkm->setSecondAbilityFlag(abilityFld->currentIndex() != 0);
	pkm->experience = experienceFld->unsignedValue();
	pkm->partyData.level = (u8)levelFld->unsignedValue();

	pkm->heldItem = heldItemFld->currentItemIndex();
	pkm->happiness = (u8)happinessFld->unsignedValue();
	pkm->pkrsStatus = (u8)((pkrsDaysRemainingFld->unsignedValue() << 4) | pkrsStrainFld->unsignedValue());
	pkm->partyData.pkrsDaysRemaining = (s8)(partyPrksDaysRemainingFld->value());

	pkm->partyData.status = (statusFld->currentIndex() == 0) ? NoStatus : (PokemonStatus)(2 + statusFld->currentIndex());
	pkm->partyData.turnsOfBadPoison = (s8)turnsOfBadPoisonFld->value();
	pkm->partyData.turnsOfSleepRemaining = (s8)turnsOfSleepRemainingFld->value();

	QCheckBox* g1[] = { eggFlagCheckBox, secondAbilityFlagCheckBox, invalidPokemonCheckBox,
						notTradableInGameFlagCheckBox, unknownFlagCheckBox, caughtFlagCheckBox };

	for (size_t i = 0; i < 3; ++i) {
		pkm->pkmFlags[i] = g1[i]->isChecked();
		if (isXD)
			static_cast<XD::Pokemon*>(pkm)->XDPkmFlags[i] = g1[3 + i]->isChecked();
	}

	pkm->markings.circle = circleMarkingCheckBox->isChecked();
	pkm->markings.square = squareMarkingCheckBox->isChecked();
	pkm->markings.triangle = triangleMarkingCheckBox->isChecked();
	pkm->markings.heart = heartMarkingCheckBox->isChecked();

	pkm->locationCaught = (u8)locationCaughtFld->unsignedValue();
	pkm->levelMet = (u8)levelMetFld->unsignedValue();
	pkm->ballCaughtWith = ballCaughtWithFld->currentItemIndex();
	pkm->obedient = obedientFld->isChecked();

	OTField->trainerName(pkm->OTName);
	pkm->TID = OTField->TID();
	pkm->SID = OTField->SID();
	pkm->OTGender = OTField->trainerGender();
	
	pkm->version = versionFld->info();

	pkm->partyData.currentHP = currentHPFld->unsignedValue();
	for (size_t i = 0; i < 6; ++i) {
		PokemonStatLayout* l = mainStatsFlds[i];
		pkm->IVs[i] = (u8)l->IVFld->unsignedValue();
		pkm->EVs[i] = (u8)l->EVFld->unsignedValue();
		pkm->partyData.stats[i] = (u16)l->statFld->unsignedValue();
	}

	for (size_t i = 0; i < 4; ++i)
		pkm->moves[i] = moveLayouts[i]->move();
	for (size_t i = 0; i < 5; ++i)
		pkm->contestAchievements[i] = (ContestAchievementLevel) contestAchievementFlds[i]->currentIndex();
	for (size_t i = 0; i < 12; ++i)
		pkm->specialRibbons[i] = specialRibbonsFlds[i]->isChecked();
}

QString PokemonUI::getShortPkmAttributeText(LibPkmGC::PokemonSpeciesIndex species, LibPkmGC::u32 PID, LibPkmGC::u16 TID, LibPkmGC::u16 SID){
	QString ret;

	bool shiny = Base::Pokemon::isShiny(PID, TID,SID);
	if (shiny) {
		ret += "<span style='color:red;'>\xe2\x98\x85</span>";
	}

	if (Base::Pokemon::getGender(species, PID) == Male)
		ret += "<span style='color:blue;'>\xe2\x99\x82</span>";

	else if (Base::Pokemon::getGender(species, PID) == Female)
		ret += "<span style='color:magenta;'>\xe2\x99\x80</span>";
	else {
		if (!ret.isEmpty()) ret += ",";

		ret += " <span style='color:green;'>";
		ret += tr("Genderless");
		ret += "</span>";
	}
	return ret;
}

QString PokemonUI::getLongPkmAttributeText(LibPkmGC::PokemonSpeciesIndex species, LibPkmGC::u32 PID, LibPkmGC::u16 TID, LibPkmGC::u16 SID)
{
	QString ret = getShortPkmAttributeText(species, PID, TID, SID);
	LanguageIndex lg = generateDumpedNamesLanguage();
	
	if (!ret.isEmpty()) ret += ", ";

	ret += getPokemonNatureName(lg, Base::Pokemon::getNature(PID));
	if (species == Unown) {
		if (!ret.isEmpty()) ret += ", ";
		ret += tr("Unown form: ");
		ret += Base::Pokemon::getUnownForm(PID);
	}
	if (species == Wurmple) {
		if (!ret.isEmpty()) ret += ", ";
		ret += tr("will evolve into: ");
		ret += getPokemonSpeciesName(lg, Base::Pokemon::getWurmpleEvolution(PID));
	}
	return ret;
}

QString PokemonUI::getShortPkmAttributeText(void){
	const QString invalid = "<span style='color:red;'>INVALID</span>";
	QString ret, tt;
	if (pkm == NULL || speciesFld->currentIndex() == 0) return "";
	
	if (versionFld->info().isIncomplete())
		tt = tr("Invalid version info");
	if (isXD && invalidPokemonCheckBox->isChecked()) {
		if (!tt.isEmpty()) tt += "\n";
		tt += tr("\"Invalid Pok\xc3\xa9mon\" flag set");
	}

	attributesFld->setToolTip(tt);

	if (!tt.isEmpty()) {
		return invalid;
	}

	u32 PID = (u32)PIDFld->value();
	PokemonSpeciesIndex species = nameIndexToPkmSpeciesIndex((size_t)speciesFld->currentIndex());
	u16 TID = OTField->TID(), SID  = OTField->SID();
	return getShortPkmAttributeText(species, PID, TID, SID);
}

QString PokemonUI::getLongPkmAttributeText(void){
	const QString invalid = "<span style='color:red;'>INVALID</span>";
	QString ret, tt;
	if (pkm == NULL || speciesFld->currentIndex() == 0) return "";

	if (versionFld->info().isIncomplete())
		tt = tr("Invalid version info");
	if (isXD && invalidPokemonCheckBox->isChecked()) {
		if (!tt.isEmpty()) tt += "\n";
		tt += tr("\"Invalid Pok\xc3\xa9mon\" flag set");
	}

	attributesFld->setToolTip(tt);

	if (!tt.isEmpty()) {
		return invalid;
	}

	u32 PID = (u32)PIDFld->value();
	PokemonSpeciesIndex species = nameIndexToPkmSpeciesIndex((size_t)speciesFld->currentIndex());
	u16 TID = OTField->TID(), SID = OTField->SID();

	return getLongPkmAttributeText(species, PID, TID, SID);
}

void PokemonUI::updateMainStats(void) {
	if (autoUpdateMainStatsCheckBox->isChecked()) {
		for (size_t i = 0; i < 6; ++i) {
			PokemonSpeciesIndex id = (PokemonSpeciesIndex)Localization::nameIndexToPkmSpeciesIndex((size_t)speciesFld->currentIndex());
			PokemonStatLayout* l = mainStatsFlds[i];
			PokemonNatureIndex natureIndex = (PokemonNatureIndex)((u32)PIDFld->value() % 25);
			u16 stat = Base::Pokemon::calculateStat(i, id, natureIndex, 
														     (u8) levelFld->value(), (u8) l->IVFld->value(), (u8) l->EVFld->value());
			l->statFld->setUnsignedValue(stat);
		}
		currentHPFld->setUnsignedValue(mainStatsFlds[0]->statFld->value());

	}
	currentHPFld->setUnsignedMaximum(mainStatsFlds[0]->statFld->value());

}

void PokemonUI::updatePkmAttributes(void) {
	attributesFld->setText(getLongPkmAttributeText());
}

void PokemonUI::updateAbilityList(void) {
	LanguageIndex lg = generateDumpedNamesLanguage();
	PokemonSpeciesIndex id = Localization::nameIndexToPkmSpeciesIndex((size_t)speciesFld->currentIndex());
	const PokemonAbilityIndex* ab = getSpeciesData(id).possibleAbilities;
	bool sec = abilityFld->currentIndex() == 1;

	abilityFld->disconnect(SIGNAL(currentIndexChanged(int)), this);
	secondAbilityFlagCheckBox->disconnect(SIGNAL(stateChanged(int)), this);

	abilityFld->clear();
	abilityFld->addItem(Localization::getPokemonAbilityName(lg, ab[0]));
	if (ab[1] != NoAbility) {
		abilityFld->addItem(Localization::getPokemonAbilityName(lg, ab[1]));
		abilityFld->setDisabled(false);
		abilityFld->setCurrentIndex((sec) ? 1 : 0);
	}
	else {
		abilityFld->setDisabled(true);
	}

	updateFlags();
	connect(abilityFld, SIGNAL(currentIndexChanged(int)), this, SLOT(updateFlags()));
	connect(secondAbilityFlagCheckBox, SIGNAL(stateChanged(int)), this, SLOT(flagsStateChangeHandler()));
}


void PokemonUI::updateExperienceFromLevel(bool proportionally) {
	if (syncLevelAndExpFldsCheckBox->isChecked()) {
		u32 experience = 0;
		if (!proportionally) {
			u8 lvl = Base::Pokemon::calculateLevelFromExp(nameIndexToPkmSpeciesIndex((size_t)speciesFld->currentIndex()), (u32)experienceFld->value());
			if (lvl == levelFld->unsignedValue()) return;
			experience = Base::Pokemon::calculateExpFromLevel(nameIndexToPkmSpeciesIndex((size_t)speciesFld->currentIndex()), (u8)levelFld->value());
		}
		else {
			experience = Base::Pokemon::fixExperienceProportionally(oldSpecies, experienceFld->unsignedValue(), nameIndexToPkmSpeciesIndex(speciesFld->currentIndex()));
		}
		experienceFld->disconnect(SIGNAL(valueChanged(int)), this);
		experienceFld->setValue((int)experience);
		connect(experienceFld, SIGNAL(valueChanged(int)), this, SLOT(updateLevelFromExperience()));
	}
	updateMainStats();
}

void PokemonUI::updateLevelFromExperience(void) {
	if (syncLevelAndExpFldsCheckBox->isChecked()) {
		u8 lvl = Pokemon::calculateLevelFromExp(nameIndexToPkmSpeciesIndex((size_t)speciesFld->currentIndex()), (u32)experienceFld->value());
		
		levelFld->disconnect(SIGNAL(valueChanged(int)), this);
		levelFld->setUnsignedValue(lvl);
		connect(levelFld, SIGNAL(valueChanged(int)), this, SLOT(updateExperienceFromLevel()));
	}
	updateMainStats();

}

void PokemonUI::speciesChangeHandler(void) {
	updatePkmAttributes();
	autoUpdateStatsStateChangeHandler(); // update stats etc...
	updateAbilityList();
	u32 maxExperience = Pokemon::calculateExpFromLevel(nameIndexToPkmSpeciesIndex((size_t)speciesFld->currentIndex()), 100);
	experienceFld->setUnsignedRange(0, maxExperience);
	updateExperienceFromLevel(oldSpecies != (PokemonSpeciesIndex)-1);
	if (oldSpecies != (PokemonSpeciesIndex)-1) oldSpecies = nameIndexToPkmSpeciesIndex(speciesFld->currentIndex());
}

void PokemonUI::PIDChangeHandler(void) {
	updatePkmAttributes();
	updateMainStats();
}

void PokemonUI::updatePkrsDaysRemaining(void) {
	if (pkrsStrainFld->unsignedValue() == 0) {
		pkrsDaysRemainingFld->setValue(0);
		pkrsDaysRemainingFld->setDisabled(true);
		partyPrksDaysRemainingFld->setRange(-1, -1);
		partyPrksDaysRemainingFld->setValue(-1);
		partyPrksDaysRemainingFld->setDisabled(true);
	}
	else {
		pkrsDaysRemainingFld->setDisabled(false);
		partyPrksDaysRemainingFld->setDisabled(false);
		pkrsDaysRemainingFld->setUnsignedRange(0, (pkrsStrainFld->unsignedValue() & 0x3) + 1);
		partyPrksDaysRemainingFld->setRange(0, (pkrsStrainFld->unsignedValue() & 0x3) + 1);
	}
}

void PokemonUI::statusChangeHandler(void) {
	PokemonStatus status = (statusFld->currentIndex() == 0) ? NoStatus : (PokemonStatus)(2 + statusFld->currentIndex());
	if (status != BadlyPoisoned) {
		turnsOfBadPoisonFld->setValue(0);
		turnsOfBadPoisonFld->setDisabled(true);
	}
	else {
		turnsOfBadPoisonFld->setDisabled(false);
	}

	if (status != Asleep) {
		turnsOfSleepRemainingFld->setValue(0);
		turnsOfSleepRemainingFld->setDisabled(true);
	}
	else {
		turnsOfSleepRemainingFld->setDisabled(false);
	}

}

void PokemonUI::updateFlags(void) {
	secondAbilityFlagCheckBox->setDisabled(abilityFld->count() == 1);
	secondAbilityFlagCheckBox->setChecked(abilityFld->currentIndex() == 1);
}

void PokemonUI::flagsStateChangeHandler(void) {
	abilityFld->setCurrentIndex((secondAbilityFlagCheckBox->isChecked() && abilityFld->count() == 2) ? 1 : 0);
	updatePkmAttributes();
}

void PokemonUI::autoUpdateStatsStateChangeHandler(void) {
	bool checked = autoUpdateMainStatsCheckBox->isChecked();
	if (checked) updateMainStats();
	currentHPFld->setDisabled(checked);
	for (size_t i = 0; i < 6; ++i) mainStatsFlds[i]->statFld->setDisabled(checked);
}

void PokemonUI::versionChangeHandler(void) {
	if (pkm == NULL) return;
	VersionInfo v = versionFld->info();
	QLabel* l = (QLabel*) coreCaptureInfoLayout->labelForField(locationCaughtFld);
	if (v.game != Colosseum_XD)
		l->setText(tr("Location caught (see <a href='http://bulbapedia.bulbagarden.net/wiki/List_of_locations_by_index_number_(Generation_III)'>here</a>)"));
	else
		l->setText(tr("Location caught (see <a href='http://bulbapedia.bulbagarden.net/wiki/List_of_locations_by_index_number_(GCN)'>here</a>)"));

	l->setOpenExternalLinks(true);

	if (speciesFld->currentIndex() != 0 && v.isIncomplete())
		QMessageBox::warning(this, tr("Warning"), tr("The version info you specified is invalid. The game will therefore consider this Pok\xc3\xa9mon invalid."));

	updatePkmAttributes();
}

void PokemonUI::resetName(void) {
	nameFld->setText(getPokemonSpeciesName(versionFld->info().language, nameIndexToPkmSpeciesIndex(speciesFld->currentIndex())));
}

void PokemonUI::copyInfoFromSave(void) {
	GC::PlayerData* pl = currentSaveSlot->player;
	OTField->set(pl->trainer->trainerName, pl->trainer->TID, pl->trainer->SID, pl->trainerGender);
	versionFld->setInfo(currentSaveSlot->gameConfig->version);
}

void PokemonUI::generateShinyIDs(void) {
	OTField->setTID((u16)(PIDFld->unsignedValue() >> 16));
	OTField->setSID((u16)PIDFld->unsignedValue());
}


}