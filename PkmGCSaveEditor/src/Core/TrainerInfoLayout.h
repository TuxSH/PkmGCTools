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
	void TIDorSIDChangedEmmiter(void);
private:
	QHBoxLayout* genderLayout;
	QButtonGroup* genderButtonGroup;
	QRadioButton *maleButton, *femaleButton;
	QLineEdit* nameFld;
	QHBoxLayout* TIDSIDLayout;
	UnsignedSpinbox<16> *SIDFld, *TIDFld;

};

#endif