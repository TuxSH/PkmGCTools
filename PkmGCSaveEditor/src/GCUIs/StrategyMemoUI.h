#ifndef _PKMGCSAVEEDITOR_STRATEGY_MEMO_UI_H
#define _PKMGCSAVEEDITOR_STRATEGY_MEMO_UI_H

#include <GCUIs/StrategyMemoEntryWidget.h>

namespace GCUIs {

class StrategyMemoUI : public DataUI {
	Q_OBJECT
public:
	StrategyMemoUI(LibPkmGC::GC::StrategyMemoData* inStrategyMemo = NULL, QWidget* parent = NULL, Qt::WindowFlags f = Qt::Window);
	~StrategyMemoUI(void);

	LibPkmGC::GC::StrategyMemoData* strategyMemo;
	LibPkmGC::GC::StrategyMemoData* strategyMemoBackup;
	
	void parseData(void);
	void saveChanges(void);
	void cancelChanges(void);
public slots:
	void updateEntryNameAndNbEntries(int index, size_t nameIndex);
	void setCurrentEntry(int index);
protected:
	void initWidget(void);
private:
	void updateEntryName(int index, size_t nameIndex);
	QFormLayout *entrySelectorLayout;
	UnsignedSpinbox<16>* nbEntriesFld;
	QComboBox *entrySelector;

	StrategyMemoEntryWidget* currentEntry; // we cannot use a QStackedWidget here
};

}

#endif