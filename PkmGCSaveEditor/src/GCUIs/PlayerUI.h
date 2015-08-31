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