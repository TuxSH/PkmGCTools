#ifndef _PKMGCSAVEEDITOR_STRATEGY_MEMO_ENTRY_WIDGET_H
#define _PKMGCSAVEEDITOR_STRATEGY_MEMO_ENTRY_WIDGET_H

#include <Core/DataUI.h>
#include <Core/UnsignedSpinbox.h>
#include <QLabel>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QCheckBox>
#include <QRadioButton>
#include <QComboBox>
#include <QStackedWidget>
#include <QPushButton>

namespace GCUIs {

class StrategyMemoEntryWidget : public QWidget, public IDataUI {
	Q_OBJECT
public:
	StrategyMemoEntryWidget(LibPkmGC::GC::StrategyMemoEntry* inEntry = NULL, int inEntryIndex = 0, QWidget* parent = NULL);
	~StrategyMemoEntryWidget(void);

	LibPkmGC::GC::StrategyMemoEntry *entry, *entryBackup;
	int entryIndex;

	void parseData(void);
	void saveChanges(void);

signals:
	void speciesChanged(int index, size_t nameIndex);
	public slots:
	void speciesChangeHandler(int nameIndex);
	void updatePIDText(void);
	void generateShinyPID(void);
protected:
	void initWidget(void);

private:
	bool isXD;
	QVBoxLayout *mainLayout;
	QFormLayout *mainLayout2;
	QComboBox *speciesSelector;

	QCheckBox *partialInfoCheckBox;

	UnsignedSpinbox<16> *firstTIDFld, *firstSIDFld;
	QVBoxLayout* PIDLayout;
	UnsignedSpinbox<32> *firstPIDFld;
	QLabel* PIDText;
	QPushButton* generateShinyPIDButton;
};


}

#endif