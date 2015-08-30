#ifndef _PKMGCSAVEEDITOR_MAIN_WINDOW_H
#define _PKMGCSAVEEDITOR_MAIN_WINDOW_H

#include <GCUIs/GameConfigUI.h>
#include <GCUIs/PlayerUI.h>
#include <GCUIs/PCUI.h>
#include <GCUIs/DaycareUI.h>
#include <GCUIs/StrategyMemoUI.h>
#include <XDUIs/PurifierUI.h>
#include <QGridLayout>
#include <QMainWindow>
#include <QScopedPointer>
#include <QCloseEvent>
#include <QSettings>
#include <QTranslator>
#include <QActionGroup>

class MWCentralWidget : public QWidget {
	Q_OBJECT
public:
	MWCentralWidget(QWidget* parent = NULL, Qt::WindowFlags f = 0);

	void updateText(void);

public slots:
	void currentSaveSlotChangeHandler(void);
	void openGameConfigUI(void);
	void openPlayerUI(void);
	void openPCUI(void);
	void openDaycareUI(void);
	void openStrategyMemoUI(void);
	void openPurifierUI(void);

private:
	QVBoxLayout *mainLayout;
	QPushButton *gameConfigButton, *playerButton, *PCButton, *daycareButton, *strategyMemoButton, *purifierButton ;
};

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow();

	void updateText(void);
	void updateStatusBar(void);
	int openSaveChangesPrompt(void);
public slots:
	void openSaveFile(void);
	bool saveSaveFile(void);
	void saveSaveFileAs(void);

	void loadSettings(void);
	void saveSettings(void);

	void interfaceLanguageChanged(QAction* action);
	void dumpedNamesLanguageChanged(QAction* action);



protected:
	void closeEvent(QCloseEvent* ev);
	void changeEvent(QEvent* ev);

private:
	QString loadInterfaceLanguage(QString const& language);

	void createInterfaceLanguageMenu(void);
	void createDumpedNamesLanguageMenu(void);
	void switchTranslator(QTranslator& translator, QString const& filename);
	QScopedPointer<LibPkmGC::GC::SaveEditing::Save> saveFile; // global public access is done through ::currentSave
	MWCentralWidget *centralWidget;

	QMenu *fileMenu;
	QAction *openFileAction, *saveFileAction, *saveFileAsAction, *exitAction;

	QMenu *optionsMenu;
	QAction* ignoreDataCorruptionAction;
	QMenu* interfaceLangSubMenu;
	QActionGroup *interfaceLangGroup;
	QMenu* dumpedNamesLangSubMenu;
	QActionGroup *dumpedNamesLangGroup;
	QSettings *settings;

	QTranslator translator, translatorQt;

	QString langPath;

};

#endif