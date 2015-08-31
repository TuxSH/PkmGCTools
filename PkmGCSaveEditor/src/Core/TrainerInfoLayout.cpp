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

#include <Core/TrainerInfoLayout.h>

using namespace LibPkmGC;
TrainerInfoLayout::TrainerInfoLayout(LibPkmGC::Base::PokemonString* inName, LibPkmGC::u16 inTID, LibPkmGC::u16 inSID, LibPkmGC::Gender inGender) :
QFormLayout(){
	genderLayout = new QHBoxLayout;
	TIDSIDLayout = new QHBoxLayout;
	genderButtonGroup = new QButtonGroup;
	maleButton = new QRadioButton(tr("Male", "Trainer")); femaleButton = new QRadioButton(tr("Female", "Trainer"));
	nameFld = new QLineEdit;
	TIDFld = new UnsignedSpinbox<16>; SIDFld = new UnsignedSpinbox<16>;

	genderButtonGroup->addButton(maleButton, 0);
	genderButtonGroup->addButton(femaleButton, 1);

	genderLayout->addWidget(maleButton);
	genderLayout->addWidget(femaleButton);

	TIDSIDLayout->addWidget(TIDFld); TIDSIDLayout->addWidget(SIDFld);

	nameFld->setMaxLength(10);
	this->addRow(tr("Gender", "Trainer"), genderLayout);
	this->addRow(tr("Name"), nameFld);
	this->addRow(tr("TID/SID"), TIDSIDLayout);
	set(inName, inSID, inTID, inGender);
	connect(TIDFld, SIGNAL(valueChanged(int)), this, SLOT(TIDorSIDChangedEmitter()));
	connect(SIDFld, SIGNAL(valueChanged(int)), this, SLOT(TIDorSIDChangedEmitter()));
	emit TIDorSIDChanged();
}

void TrainerInfoLayout::trainerName(LibPkmGC::Base::PokemonString * outName) {
	outName->fromUTF8(nameFld->text().toUtf8().data());
}

u16 TrainerInfoLayout::TID(void) const {
	return (u16) TIDFld->value();
}

u16 TrainerInfoLayout::SID(void) const {
	return (u16) SIDFld->value();
}

Gender TrainerInfoLayout::trainerGender(void) const {
	return (maleButton->isChecked()) ? Male : Female;
}

void TrainerInfoLayout::setTrainerName(LibPkmGC::Base::PokemonString* inName) {
	if(inName != NULL) nameFld->setText(inName->toUTF8());
}

void TrainerInfoLayout::setTID(LibPkmGC::u16 inTID) {
	TIDFld->setValue((int)inTID);
}

void TrainerInfoLayout::setSID(LibPkmGC::u16 inSID) {
	SIDFld->setValue((int)inSID);
}

void TrainerInfoLayout::setTrainerGender(LibPkmGC::Gender inGender){
	maleButton->setChecked(inGender == LibPkmGC::Male);
	femaleButton->setChecked(inGender == LibPkmGC::Female);
}

void TrainerInfoLayout::set(LibPkmGC::Base::PokemonString * inName, LibPkmGC::u16 inTID, LibPkmGC::u16 inSID, LibPkmGC::Gender inGender){
	setTrainerName(inName);
	setTID(inTID);
	setSID(inSID);
	setTrainerGender(inGender);
}

void TrainerInfoLayout::TIDorSIDChangedEmitter(void) {
	emit TIDorSIDChanged();
}