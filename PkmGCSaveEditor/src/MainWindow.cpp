#include <MainWindow.h>
#include <QMenuBar>
#include <QMap>
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QStatusBar>
#include <QLocale>
#include <QApplication>
#include <QDir>


const QString appName = QString("PkmGCSaveEditor v%1.%2").arg(PKMGCSAVEEDITOR_VERSION_MAJOR).arg(PKMGCSAVEEDITOR_VERSION_MINOR);

using namespace GCUIs;
using namespace XDUIs;
using namespace LibPkmGC;


MWCentralWidget::MWCentralWidget(QWidget* parent, Qt::WindowFlags f) : QWidget(parent, f), mainLayout(new QVBoxLayout) {
	gameConfigButton = new QPushButton;
	playerButton = new QPushButton;
	PCButton = new QPushButton;
	daycareButton = new QPushButton;
	strategyMemoButton = new QPushButton;
	purifierButton = new QPushButton;

	updateText();
	QPushButton* lst[] = { gameConfigButton, playerButton, PCButton, daycareButton, strategyMemoButton, purifierButton };

	for (int i = 0; i < 6; ++i)
		mainLayout->addWidget(lst[i]);
	
	this->setLayout(mainLayout);
	connect(gameConfigButton, SIGNAL(clicked()), this, SLOT(openGameConfigUI()));
	connect(playerButton, SIGNAL(clicked()), this, SLOT(openPlayerUI()));
	connect(PCButton, SIGNAL(clicked()), this, SLOT(openPCUI()));
	connect(daycareButton, SIGNAL(clicked()), this, SLOT(openDaycareUI()));
	connect(strategyMemoButton, SIGNAL(clicked()), this, SLOT(openStrategyMemoUI()));
	connect(purifierButton, SIGNAL(clicked()), this, SLOT(openPurifierUI()));
	
	currentSaveSlotChangeHandler();
}

void MWCentralWidget::updateText(void) {
	gameConfigButton->setText(tr("Game configuration"));
	playerButton->setText(tr("Trainer info, Party and Bag"));
	PCButton->setText(tr("PC"));
	daycareButton->setText(tr("Daycare"));
	strategyMemoButton->setText(tr("Strategy memo"));
	purifierButton->setText(tr("Purifier"));
}

void MWCentralWidget::currentSaveSlotChangeHandler(void) {
	QPushButton* lst[] = { gameConfigButton, playerButton, PCButton, daycareButton, strategyMemoButton, purifierButton };
	for (size_t i = 0; i < 6; ++i)
		lst[i]->setDisabled(currentSaveSlot == NULL);
	purifierButton->setVisible(currentSaveSlot != NULL && LIBPKMGC_IS_XD(SaveEditing::SaveSlot, currentSaveSlot));
}

#define GEN_GCUI_SLT(cls, obj)\
void MWCentralWidget::open##cls(void){\
cls dlg(obj, this); \
dlg.exec();\
if(changesMade) ((QWidget*)parent())->setWindowTitle("PkmGCSaveEditor - " + currentSaveFileName + "*");\
}

GEN_GCUI_SLT(GameConfigUI, currentSaveSlot)
GEN_GCUI_SLT(PlayerUI, currentSaveSlot->player)
GEN_GCUI_SLT(PCUI, currentSaveSlot->PC)
GEN_GCUI_SLT(DaycareUI, currentSaveSlot->daycare)
GEN_GCUI_SLT(StrategyMemoUI, currentSaveSlot->strategyMemo)

void MWCentralWidget::openPurifierUI(void) {
	if (!LIBPKMGC_IS_XD(SaveEditing::SaveSlot, currentSaveSlot)) return;
	PurifierUI dlg(static_cast<XD::SaveEditing::SaveSlot*>(currentSaveSlot)->purifier, this);
	dlg.exec();
}


MainWindow::MainWindow() : QMainWindow(), centralWidget(new MWCentralWidget) {
	this->setWindowTitle(appName);
	this->setWindowIcon(QIcon(":/PkmGCSaveEditor.ico"));
	fileMenu = menuBar()->addMenu(tr("&File"));

	openFileAction = new QAction(this);
	openFileAction->setShortcut(QKeySequence::Open);
	saveFileAction = new QAction(this);
	saveFileAction->setShortcut(QKeySequence::Save);
	saveFileAsAction = new QAction(this);
	saveFileAsAction->setShortcut(QKeySequence::SaveAs);
	exitAction = new QAction(this);
	exitAction->setShortcut(QKeySequence::Quit);
	
	fileMenu->addAction(openFileAction);
	fileMenu->addAction(saveFileAction);
	fileMenu->addAction(saveFileAsAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);
	
	optionsMenu = menuBar()->addMenu(tr("&Options"));
	interfaceLangSubMenu = optionsMenu->addMenu(tr("&Interface language"));
	dumpedNamesLangSubMenu = optionsMenu->addMenu(tr("&Dumped names language"));

	
	setCentralWidget(centralWidget);

	connect(openFileAction, SIGNAL(triggered()), this, SLOT(openSaveFile()));
	connect(saveFileAction, SIGNAL(triggered()), this, SLOT(saveSaveFile()));
	connect(saveFileAsAction, SIGNAL(triggered()), this, SLOT(saveSaveFileAs()));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

	loadSettings();
	createInterfaceLanguageMenu();
	createDumpedNamesLanguageMenu();
	interfaceLanguageChanged(interfaceLangGroup->checkedAction());
	dumpedNamesLanguageChanged(dumpedNamesLangGroup->actions()[(size_t)dumpedNamesLanguage]);

	updateStatusBar();

	saveFileAction->setDisabled(true);
	saveFileAsAction->setDisabled(true);
}

void MainWindow::createDumpedNamesLanguageMenu(void) {
	dumpedNamesLangGroup = new QActionGroup(dumpedNamesLangSubMenu);
	dumpedNamesLangGroup->setExclusive(true);

	QAction* select_auto = new QAction(this);
	select_auto->setCheckable(true);
	select_auto->setData(0);

	connect(dumpedNamesLangGroup, SIGNAL(triggered(QAction*)), this, SLOT(dumpedNamesLanguageChanged(QAction*)));

	dumpedNamesLangGroup->addAction(select_auto);
	dumpedNamesLangSubMenu->addAction(select_auto);

	for (int i = 1; i < 7; ++i) {
		QAction* action = new QAction(this);
		action->setCheckable(true);
		action->setData(i);
		dumpedNamesLangGroup->addAction(action);
		dumpedNamesLangSubMenu->addAction(action);	
	}

	dumpedNamesLangGroup->actions()[(size_t)dumpedNamesLanguage]->setChecked(true);
}

void MainWindow::createInterfaceLanguageMenu(void) {
	// Adapted from : https://wiki.qt.io/How_to_create_a_multi_language_application
	interfaceLangGroup = new QActionGroup(interfaceLangSubMenu);
	interfaceLangGroup->setExclusive(true);

	QAction* select_auto = new QAction(this);
	select_auto->setCheckable(true);
	select_auto->setData("auto");

	interfaceLangSubMenu->addAction(select_auto);
	interfaceLangGroup->addAction(select_auto);

	connect(interfaceLangGroup, SIGNAL(triggered(QAction*)), this, SLOT(interfaceLanguageChanged(QAction*)));


	langPath = QApplication::applicationDirPath().append("/translations/");
	QStringList fileNames = QDir(langPath).entryList(QStringList("PkmGCSaveEditor_*.qm"));

	QAction *actionToCheck = select_auto;

	for (int i = 0; i < fileNames.size(); ++i) {
		QString locale;
		locale = fileNames[i];
		locale.truncate(locale.lastIndexOf('.'));
		locale.remove(0, locale.indexOf('_') + 1);

		QAction *action = new QAction(this);
		if (locale == interfaceLanguage) actionToCheck = action;

		action->setCheckable(true);
		action->setData(locale);

		interfaceLangGroup->addAction(action);
		interfaceLangSubMenu->addAction(action);
	}

	actionToCheck->setChecked(true);
}

void MainWindow::updateText(void) {
	centralWidget->updateText();
	fileMenu->setTitle(tr("&File"));
	
	openFileAction->setText(tr("&Open..."));
	saveFileAction->setText(tr("&Save"));
	saveFileAsAction->setText(tr("Save &as..."));
	exitAction->setText(tr("&Exit"));

	optionsMenu->setTitle(tr("&Options"));
	interfaceLangSubMenu->setTitle(tr("&Interface language"));
	dumpedNamesLangSubMenu->setTitle(tr("&Dumped names language"));
	
	QList<QAction*> actions = interfaceLangGroup->actions(), actions2 = dumpedNamesLangGroup->actions();

	actions[0]->setText(tr("Select &automatically"));
	actions2[0]->setText(tr("Select &automatically"));

	for (QList<QAction*>::iterator it = actions.begin() + 1; it != actions.end(); ++it)
		(*it)->setText(VersionInfoLayout::languageNames()[languageCodeToIndexMap[(*it)->data().toString()]]);

	for (QList<QAction*>::iterator it = actions2.begin() + 1; it != actions2.end(); ++it)
		(*it)->setText(VersionInfoLayout::languageNames()[(*it)->data().toInt()]);
}


void MainWindow::switchTranslator(QTranslator& translator, QString const& filename) {
	// remove the old translator
	qApp->removeTranslator(&translator);

	// load the new translator
	if (translator.load(filename))
		qApp->installTranslator(&translator);
}

QString MainWindow::loadInterfaceLanguage(QString const& language) {
	if (!openFileAction->text().isEmpty() && interfaceLanguage != "auto" && interfaceLanguage == language) return language;
	QString sys_language = QLocale::system().name();
	sys_language.truncate(sys_language.lastIndexOf('_'));

	QString langPath = QApplication::applicationDirPath().append("/translations/");
	QString lg = (language == "auto") ? sys_language : language;
	QString fileName = langPath +QString("PkmGCSaveEditor_%1.qm").arg(lg);
	if (!QFile(fileName).exists()) {
		fileName = langPath + QString("PkmGCSaveEditor_en.qm");
		lg = "en";
	}
	if (!QFile(fileName).exists()) {
		updateText();
		return lg;
	}

	QLocale locale = QLocale(lg);
	QLocale::setDefault(locale);
	
	switchTranslator(translator, fileName);
	switchTranslator(translatorQt, langPath + QString("qt_%1.qm").arg(lg)); // Note that qt_en.qm does not exist, which is normal :)
	switchTranslator(translatorQt, langPath + QString("qtbase_%1.qm").arg(lg)); // For Qt > 5.3


	updateText();
	return lg;
}

void MainWindow::interfaceLanguageChanged(QAction* action) {
	if (action != NULL) interfaceLanguage = loadInterfaceLanguage(action->data().toString());
}

void MainWindow::dumpedNamesLanguageChanged(QAction* action) {
	if (action != NULL) dumpedNamesLanguage = (LanguageIndex)action->data().toInt();
}

void MainWindow::changeEvent(QEvent* ev) {
	if (ev == NULL) return;
	switch (ev->type()) {
	case QEvent::LanguageChange: updateText(); break;
	case QEvent::LocaleChange: if (interfaceLangGroup->actions()[0]->isChecked()) loadInterfaceLanguage("auto"); break;
	default: break;
	}
	QMainWindow::changeEvent(ev);
}

void MainWindow::closeEvent(QCloseEvent* ev) {
	if (!changesMade) {
		saveSettings();
		ev->accept();
	}
	else {
		switch (openSaveChangesPrompt()) {
		case QMessageBox::Save: saveSaveFile();
		case QMessageBox::Discard: saveSettings(); ev->accept(); break;
		case QMessageBox::Cancel: default: ev->ignore(); break;
		}
	}
}


int MainWindow::openSaveChangesPrompt(void) {
	const QString gcifilter = tr("GCI save files (*.gci)");
	const QString rawfilter = tr("Raw save files (*.bin)");
	QMessageBox msgBox;
	msgBox.setText(tr("The save file has been modified."));
	msgBox.setInformativeText(tr("Do you want to save your changes?"));
	msgBox.setStandardButtons((QFlags<QMessageBox::StandardButton>)((int)QMessageBox::Save | (int)QMessageBox::Discard | (int)QMessageBox::Cancel));
	msgBox.setDefaultButton(QMessageBox::Save);

	int ret = msgBox.exec();
	switch (ret){
	case QMessageBox::Save:
		saveSaveFile();
		changesMade = false;
		break;
	case QMessageBox::Discard:
		saveFile.reset();
		changesMade = false;
		break;
	case QMessageBox::Cancel:
	default:
		break;
	}
	return ret;
}

void MainWindow::openSaveFile(void) {
	const QString gcifilter = tr("GCI save files (*.gci)");
	const QString rawfilter = tr("Raw save files (*.bin)");

	const QString errmsg = tr("Could not open file.");
	const QString errmsg2 = tr("An error occured while reading the specified save file.");

	if (changesMade && (openSaveChangesPrompt() == QMessageBox::Cancel)) return;
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open save file"), lastSaveDirectory, gcifilter + ";;" + rawfilter + ";;"+tr("All Files (*)"));
	if (fileName.isEmpty()) return;

	QFileInfo fileInfo(fileName);
	size_t fileSize = (size_t)fileInfo.size();

	bool hasGCIData = false, isColosseum = false;

	switch (fileSize) {
	case 0x60040: hasGCIData = true;
	case 0x60000: isColosseum = true; break;

	case 0x56040: hasGCIData = true;
	case 0x56000: isColosseum = false; break;

	default:
		QMessageBox::critical(this, tr("Error"), tr("Invalid file size.")); return;
	}

	// Reading the save file contents ...
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::critical(this, tr("Error"), errmsg);
		return;
	}
	QByteArray ba = file.readAll();
	if (ba.size() != fileSize) {
		QMessageBox::critical(this, tr("Error"), errmsg2);
		return;
	}

	lastSaveDirectory = fileInfo.canonicalPath();
	currentSaveFileName = fileName;

	if (isColosseum)
		saveFile.reset(new Colosseum::SaveEditing::Save((const u8*)ba.data(), hasGCIData));
	else
		saveFile.reset(new XD::SaveEditing::Save((const u8*)ba.data(), hasGCIData));

	size_t slIndex = 0;
	if (ignoreDataCorruption) {
		currentSaveSlot = saveFile->getMostRecentSlot(0);
	}
	else {
		currentSaveSlot = saveFile->getMostRecentValidSlot(0, &slIndex);
		if (slIndex == 1)
			QMessageBox::warning(this, tr("Warning"), tr("The backup save slot was loaded because the most recent save slot is corrupt."));
		else if (slIndex == 2) // Colosseum only
			QMessageBox::warning(this, tr("Warning"), tr("The second backup save slot was loaded because the other ones are corrupt."));

		if (currentSaveSlot == NULL)
			QMessageBox::critical(this, tr("Error"), tr("All save slots are corrupt."));

	}

	if (currentSaveSlot == NULL) {
		currentSaveFileName = "";
		this->setWindowTitle(appName);
		saveFileAction->setDisabled(true);
		saveFileAsAction->setDisabled(true);
	}
	else {
		this->setWindowTitle(appName + " - " + currentSaveFileName);
		saveFileAction->setDisabled(false);
		saveFileAsAction->setDisabled(false);
	}

	centralWidget->currentSaveSlotChangeHandler();
	updateStatusBar();
}

void MainWindow::updateStatusBar(void) {
	if (currentSaveSlot == NULL) {
		statusBar()->showMessage(tr("No save file loaded"));
	}
	else {
		QString msg = tr("%1, %n save(s)", "", currentSaveSlot->saveCount);
		msg = msg.arg(LIBPKMGC_IS_COLOSSEUM(SaveEditing::SaveSlot, currentSaveSlot) ? tr("Colosseum") : tr("XD"));
		statusBar()->showMessage(msg);
	}
}
bool MainWindow::saveSaveFile(void) {
	const QString errmsg = tr("Could not write to file.");
	const QString errmsg2 = tr("An error occured while writing to the specified save file.");

	QString fileName = currentSaveFileName;
	if (fileName.isEmpty()) return false;

	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly)) {
		QMessageBox::critical(this, tr("Error"), errmsg);
		return false;
	}

	bool writeGCIData = (fileName.section(".", -1) == "gci") && saveFile->hasGCIData;
	int sz = saveFile->fixedSize + ((writeGCIData) ? 0x40 : 0);

	QByteArray ba(sz, '\0');
	saveFile->saveEncrypted((u8*)ba.data(), writeGCIData);

	if (file.write(ba) != (qint64)sz) {
		QMessageBox::critical(this, tr("Error"), errmsg2);
		return false;
	}

	changesMade = false;
	return true;
}

void MainWindow::saveSaveFileAs(void) {
	const QString gcifilter = tr("GCI save files (*.gci)");
	const QString rawfilter = tr("Raw save files (*.bin)");
	QString previousFileName = currentSaveFileName;

	QString filters = ((saveFile->hasGCIData) ? gcifilter + ";;" : "") + rawfilter + ";;" + tr("All files (*)");
	currentSaveFileName = QFileDialog::getSaveFileName(this, tr("Save save file"), lastSaveDirectory, filters);

	if (!saveSaveFile()) {
		currentSaveFileName = previousFileName;
	}
	else {
		lastSaveDirectory = QFileInfo(currentSaveFileName).canonicalPath();
		this->setWindowTitle(appName + " - " + currentSaveFileName);
	}

}

void MainWindow::loadSettings(void) {
	settings = new QSettings("PkmGCTools", "PkmGCSaveEditor", this);
	ignoreDataCorruption = settings->value("IgnoreDataCorruption").toBool();
	interfaceLanguage = settings->value("InterfaceLanguage").toString();
	dumpedNamesLanguage = (LanguageIndex) settings->value("DumpedNamesLanguage").toInt();

	lastPkmDirectory = settings->value("LastPkmDirectory").toString();
	lastSaveDirectory = settings->value("LastSaveDirectory").toString();

	if (interfaceLanguage.isEmpty()) interfaceLanguage = "auto";
	if (dumpedNamesLanguage > Spanish) dumpedNamesLanguage = NoLanguage;

}

void MainWindow::saveSettings(void) {
	settings->setValue("Version", PKMGCSAVEEDITOR_VERSION);
	settings->setValue("LibPkmGCVersion", LIBPKMGC_VERSION);

	settings->setValue("IgnoreDataCorruption", ignoreDataCorruption);
	settings->setValue("InterfaceLanguage", interfaceLangGroup->checkedAction()->data());
	if (dumpedNamesLanguage > Spanish) dumpedNamesLanguage = NoLanguage;
	settings->setValue("DumpedNamesLanguage", dumpedNamesLanguage);

	settings->setValue("LastPkmDirectory", lastPkmDirectory);
	settings->setValue("LastSaveDirectory", lastSaveDirectory);
}