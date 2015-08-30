#ifndef _PKMGCSAVEEDITOR_DATA_UI_H
#define _PKMGCSAVEEDITOR_DATA_UI_H

#include <Core/Globals.h>
#include <Core/IDataUI.h>
#include <QDialog>
#include <QVBoxLayout>
#include <QDialogButtonBox>

class DataUI : public QDialog, public IDataUI {
	Q_OBJECT

public:
	DataUI(QWidget* parent = NULL, Qt::WindowFlags f = Qt::Window);

public slots:
	void accept(void);
	void reject(void);
protected:
	bool isXD;

	void initWidget(void);

	QVBoxLayout *mainLayout;
	QDialogButtonBox *dialogButtonBox;
};

#endif