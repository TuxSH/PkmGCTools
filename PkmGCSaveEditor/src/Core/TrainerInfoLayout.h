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

#ifndef _PKMGCSAVEEDITOR_TRAINER_INFO_LAYOUT_H
#define _PKMGCSAVEEDITOR_TRAINER_INFO_LAYOUT_H

#include <QFormLayout>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QRadioButton>
#include <QLineEdit>
#include <algorithm>
#include <Core/UnsignedSpinbox.h>
#include <LibPkmGC/Core/PokemonInfo.h>
#include <LibPkmGC/Base/PokemonString.h>
class TrainerInfoLayout : public QFormLayout{
	Q_OBJECT
public:
	TrainerInfoLayout(LibPkmGC::Base::PokemonString *inName = NULL, LibPkmGC::u16 inTID = 0, LibPkmGC::u16 inSID = 0, LibPkmGC::Gender inGender = LibPkmGC::Male);

	void trainerName(LibPkmGC::Base::PokemonString* outName);
	LibPkmGC::u16 TID(void) const;
	LibPkmGC::u16 SID(void) const;
	LibPkmGC::Gender trainerGender(void) const;

	void setTrainerName(LibPkmGC::Base::PokemonString* inName);
	void setTID(LibPkmGC::u16 inTID);
	void setSID(LibPkmGC::u16 inSID);
	void setTrainerGender(LibPkmGC::Gender inGender);

	void set(LibPkmGC::Base::PokemonString *inName = NULL, LibPkmGC::u16 inTID = 0, LibPkmGC::u16 inSID = 0, LibPkmGC::Gender inGender = LibPkmGC::Male);
	
signals:
	void TIDorSIDChanged(void);

public slots:
	void TIDorSIDChangedEmitter(void);
private:
	QHBoxLayout* genderLayout;
	QButtonGroup* genderButtonGroup;
	QRadioButton *maleButton, *femaleButton;
	QLineEdit* nameFld;
	QHBoxLayout* TIDSIDLayout;
	UnsignedSpinbox<16> *SIDFld, *TIDFld;

};

#endif