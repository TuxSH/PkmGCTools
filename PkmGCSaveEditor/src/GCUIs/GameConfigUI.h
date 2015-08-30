#ifndef _PKMGCSAVEEDITOR_GAME_CONFIG_UI_H
#define _PKMGCSAVEEDITOR_GAME_CONFIG_UI_H

#include <Core/DataUI.h>
#include <Core/UnsignedSpinbox.h>
#include <Core/VersionInfoLayout.h>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QCheckBox>

namespace GCUIs {

class GameConfigUI : public DataUI {
	Q_OBJECT
public:
	GameConfigUI(LibPkmGC::GC::SaveEditing::SaveSlot *inSaveSlot = NULL, QWidget* parent = NULL, Qt::WindowFlags f = Qt::Window);

	LibPkmGC::GC::SaveEditing::SaveSlot* saveSlot_; // not using ::currentSaveSlot here 

	void parseData(void);

	void saveChanges(void);

public slots:
	void versionChangeHandler(void);
protected:
	void initWidget(void);

private:
	QGroupBox* versionBox;
	VersionInfoLayout* versionFld;

	QGroupBox* titleScreenOptionsBox;
	QFormLayout* titleScreenOptionsLayout;
	QCheckBox *noRumbleFld;
	QComboBox* titleScreenLanguageFld;

	QGroupBox* miscellaneousBox;
	QFormLayout* miscellaneousLayout;
	UnsignedSpinbox<32>* storyModeSaveCountFld;


};

}

#endif