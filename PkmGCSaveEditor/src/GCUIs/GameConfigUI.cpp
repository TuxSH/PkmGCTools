#include <GCUIs/GameConfigUI.h>
#include <QMessageBox>

using namespace LibPkmGC;
using namespace GC::SaveEditing;
namespace GCUIs {

GameConfigUI::GameConfigUI(SaveSlot * inSaveSlot, QWidget * parent, Qt::WindowFlags f) : DataUI(parent, f), saveSlot_(inSaveSlot) {
	init();
}

void GameConfigUI::initWidget(void) {
	versionBox = new QGroupBox(tr("Game version"));
	versionFld = new VersionInfoLayout;

	titleScreenOptionsBox = new QGroupBox(tr("Title screen options"));
	titleScreenOptionsLayout = new QFormLayout;
	noRumbleFld = new QCheckBox;
	titleScreenLanguageFld = new QComboBox;

	miscellaneousBox = new QGroupBox(tr("Miscellaneous"));
	miscellaneousLayout = new QFormLayout;
	storyModeSaveCountFld = new UnsignedSpinbox<32>;

	titleScreenLanguageFld->addItems(VersionInfoLayout::languageNames());

	versionBox->setLayout(versionFld);
	
	titleScreenOptionsLayout->addRow(tr("Rumble function disabled"), noRumbleFld);
	titleScreenOptionsLayout->addRow(tr("Language"), titleScreenLanguageFld);
	titleScreenOptionsBox->setLayout(titleScreenOptionsLayout);

	miscellaneousLayout->addRow(tr("Story mode save count"), storyModeSaveCountFld);
	miscellaneousBox->setLayout(miscellaneousLayout);

	mainLayout->addWidget(versionBox);
	mainLayout->addWidget(titleScreenOptionsBox);
	mainLayout->addWidget(miscellaneousBox);

	connect(versionFld, SIGNAL(versionChanged()), this, SLOT(versionChangeHandler()));
	DataUI::initWidget();
}

void GameConfigUI::parseData(void) {
	if (saveSlot_ == NULL) return;
	SaveSlot* sl = saveSlot_;
	isXD = LIBPKMGC_IS_XD(SaveEditing::SaveSlot, sl);

	versionFld->disconnect(SIGNAL(versionChanged()));
	versionFld->setInfo(sl->version);
	connect(versionFld, SIGNAL(versionChanged()), this, SLOT(versionChangeHandler()));

	noRumbleFld->setChecked(sl->noRumble);
	titleScreenLanguageFld->setCurrentIndex((int)sl->titleScreenLanguage);

	miscellaneousBox->setVisible(!isXD);
	if (!isXD) {
		Colosseum::SaveEditing::SaveSlot *sl_c = (Colosseum::SaveEditing::SaveSlot*) sl;
		storyModeSaveCountFld->setUnsignedValue(sl_c->storyModeSaveCount);
	}

	versionChangeHandler();
}

void GameConfigUI::saveChanges(void) {
	SaveSlot* sl = saveSlot_;
	
	sl->version = versionFld->info();
	sl->noRumble = noRumbleFld->isChecked();
	sl->titleScreenLanguage = (LanguageIndex)titleScreenLanguageFld->currentIndex();
	if (!isXD) {
		Colosseum::SaveEditing::SaveSlot *sl_c = (Colosseum::SaveEditing::SaveSlot*) sl;
		sl_c->storyModeSaveCount = storyModeSaveCountFld->unsignedValue();
	}

}

void GameConfigUI::versionChangeHandler(void) {
	if (versionFld->info().isIncomplete())
		QMessageBox::warning(this, tr("Warning"), tr("The version info you specified is invalid, and will make the game unplayable."));
}




}
