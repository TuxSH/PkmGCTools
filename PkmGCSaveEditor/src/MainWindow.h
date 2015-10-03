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

#ifndef _PKMGCSAVEEDITOR_MAIN_WINDOW_H
#define _PKMGCSAVEEDITOR_MAIN_WINDOW_H

#include <GCUIs/GameConfigUI.h>
#include <GCUIs/PlayerUI.h>
#include <GCUIs/PCUI.h>
#include <GCUIs/DaycareUI.h>
#include <GCUIs/StrategyMemoUI.h>
#include <GCUIs/RibbonDescriptionsUI.h>
#include <XDUIs/PurifierUI.h>
#include <QGridLayout>
#include <QMainWindow>
#include <QScopedPointer>
#include <QCloseEvent>
#include <QSettings>
#include <QTranslator>
#include <QActionGroup>
#include <QNetworkReply>
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
	void openRibbonDescriptionsUI(void);
	void openPurifierUI(void);

private:
	QVBoxLayout *mainLayout;
	QPushButton *gameConfigButton, *playerButton, *PCButton, *daycareButton, *strategyMemoButton, *ribbonDescriptionsButton, *purifierButton ;
};

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow();

	void updateText(void);
	void updateStatusBar(void);
	int openSaveChangesPrompt(void);

	void checkForUpdates(void);
public slots:
	void openSaveFile(void);
	bool saveSaveFile(void);
	void saveSaveFileAs(void);

	void loadSettings(void);
	void saveSettings(void);

	void interfaceLanguageChanged(QAction* action);
	void dumpedNamesLanguageChanged(QAction* action);

	void changeIgnoreDataCorruptionStatus(void);

	void fixColosseumBugsAffectingPokemon(void);


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
	QMenu* interfaceLangSubMenu;
	QActionGroup *interfaceLangGroup;
	QMenu* dumpedNamesLangSubMenu;
	QActionGroup *dumpedNamesLangGroup;
	QMenu* bugFixesSubMenu;
	QAction* colosseumBugsAffectingPokemonAction;
	QAction* ignoreDataCorruptionAction;
	QAction* checkForUpdatesAtStartupAction;


	QSettings *settings;

	QTranslator translator, translatorQt;

	QString langPath;

	int oldversionMax;
};

#endif