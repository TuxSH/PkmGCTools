#ifndef _PKMGCSAVEEDITOR_I_DATA_UI_H
#define _PKMGCSAVEEDITOR_I_DATA_UI_H

#include <LibPkmGC/Base/DataStruct.h>
#include <QObject>

class IDataUI {
public:
	virtual void parseData(void) = 0;
	virtual void saveChanges(void) = 0;
	virtual void cancelChanges(void) {}
protected:

	virtual void init(void) {
		initWidget();
		parseData();
	}
	virtual void initWidget(void) = 0;
};

#endif