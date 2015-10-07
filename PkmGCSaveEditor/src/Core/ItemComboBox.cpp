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

#include <Core/ItemComboBox.h>

using namespace LibPkmGC;
using namespace LibPkmGC::Localization;

ItemComboBox::ItemComboBox(unsigned int inFlags, bool isXD, QWidget* parent) : QComboBox(parent), _flags(inFlags), _isXD(isXD){
	_indices = new ItemIndex[336]; //  245 + 91
	_reverseIndices = new int[594];
	resetItemList();
}

ItemComboBox::~ItemComboBox(void){
	delete[] _indices;
	delete[] _reverseIndices;
}

void ItemComboBox::resetItemList(void){
	this->clear();
	LanguageIndex lg = generateDumpedNamesLanguage();
	int j = 0;
	_flags = (_flags == EMPTY_ITEM_FORBIDDEN) ? 0 : _flags;
	unsigned int fl = _flags;
	if ((_flags & EMPTY_ITEM_FORBIDDEN) == 0) {
		this->addItem(getItemName(lg, NoItem, _isXD));
		_reverseIndices[0] = 0;
		_indices[j++] = NoItem;
	}
	else {
		_reverseIndices[0] = -1;
	}
	fl &= ~1; // since (1 << (getItemCategory(<invalid item index>) )) == 1 ...

	for (int i = 1; i <= (int)BattleCD60; ++i) { // 593 
		ItemIndex index = (ItemIndex)i;
		unsigned int ctgFlg = (1U << (int)getItemCategory(index, _isXD));
		if ((fl & ctgFlg) != 0) {
			const char* name = getItemName(lg, index, _isXD);
			this->addItem((index >= TM01 && index <= TM50)
				? QString("%1 (%2)").arg(name).arg(getPokemonMoveName(lg, getMoveForTM(index)))
				: name
			);
			_reverseIndices[i] = j;
			_indices[j++] = index;
		}
		else {
			_reverseIndices[i] = -1;
		}
	}
}

ItemIndex ItemComboBox::currentItemIndex(void) const{
	int index = currentIndex();
	return _indices[this->currentIndex()];
}

void ItemComboBox::setCurrentItemIndex(ItemIndex index){
	if ((index > BattleCD60) || (_reverseIndices[(size_t)index] == -1)) this->setCurrentIndex(0);
	else this->setCurrentIndex(_reverseIndices[(size_t)index]);
}

unsigned int ItemComboBox::flags(void) const{
	return _flags;
}

void ItemComboBox::setFlags(unsigned int inFlags){
	_flags = inFlags;
	resetItemList();
}

bool ItemComboBox::version(void) const{
	return _isXD;
}

void ItemComboBox::setVersion(bool isXD){
	_isXD = isXD;
	resetItemList();
}

void ItemComboBox::set(unsigned int inFlags, bool isXD){
	_flags = inFlags;
	_isXD = isXD;
	resetItemList();
}
