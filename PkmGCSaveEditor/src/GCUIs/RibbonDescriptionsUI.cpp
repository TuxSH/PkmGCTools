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

#include <GCUIs/RibbonDescriptionsUI.h>

using namespace LibPkmGC; using namespace Localization; using namespace Base;

namespace GCUIs {

RibbonDescriptionsUI::RibbonDescriptionsUI(GC::RibbonDescriptionsData* inRibbonDescriptions, QWidget *parent, Qt::WindowFlags f) :
	DataUI(parent, f), ribbonDescriptions(inRibbonDescriptions) {
	init();
}

inline QStringList getRibbonDescriptionTexts(void) {
	LanguageIndex lg = generateDumpedNamesLanguage();
	QStringList ret;
	for (size_t i = 0; i < 65; ++i)
		ret.append(Localization::getRibbonDescription(lg, i));
	return ret;
}
void RibbonDescriptionsUI::initWidget(void) {
	const QStringList srNames = PokemonUI::ribbonNames();
	const QString rna = PokemonUI::ribbonHasNeverBeenMadeAvailableStr();
	const QStringList descr = getRibbonDescriptionTexts();

	descriptionsLayout = new QFormLayout;
	for (size_t i = 0; i < 11; ++i) {
		descriptionsFld[i] = new QComboBox;
		descriptionsFld[i]->addItems(descr);
		descriptionsLayout->addRow(srNames[i + 5], descriptionsFld[i]);
		if (i >= 0 && i <= 6 && i != 4 && i != 5)
			addToolTipTo((QLabel*)descriptionsLayout->labelForField(descriptionsFld[i]), rna);
	}
	descriptionsLayout->setHorizontalSpacing(20);
	mainLayout->addLayout(descriptionsLayout);
	DataUI::initWidget();
}


void RibbonDescriptionsUI::parseData(void) {
	if (ribbonDescriptions == NULL) return;
	isXD = LIBPKMGC_IS_XD(RibbonDescriptionsData, ribbonDescriptions);

	for (size_t i = 0; i < 11; ++i) 
		descriptionsFld[i]->setCurrentIndex(ribbonDescriptions->descriptions[i]);
}

void RibbonDescriptionsUI::saveChanges(void) {
	for (size_t i = 0; i < 11; ++i) 
		ribbonDescriptions->descriptions[i] = (u8)descriptionsFld[i]->currentIndex();
}


}