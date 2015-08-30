#include <Core/DataUI.h>

DataUI::DataUI(QWidget* parent, Qt::WindowFlags f) : QDialog(parent, f), IDataUI(),  mainLayout(new QVBoxLayout),
dialogButtonBox(new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel)) {
	connect(dialogButtonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(dialogButtonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void DataUI::accept(void) {
	saveChanges();
	changesMade = true;
	QDialog::accept();
}

void DataUI::reject(void) {
	cancelChanges();
	QDialog::reject();
}

void DataUI::initWidget(void) {
	mainLayout->addWidget(dialogButtonBox);
	this->setLayout(mainLayout);
}