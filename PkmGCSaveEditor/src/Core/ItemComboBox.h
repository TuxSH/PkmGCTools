#ifndef _PKMGCSAVEEDITOR_ITEM_COMBO_BOX_H
#define _PKMGCSAVEEDITOR_ITEM_COMBO_BOX_H

#include <Core/Globals.h>
#include <QComboBox>
#include <LibPkmGC/Core/Localization.h>

// (1 << ((int)categoryIndex)
#define EMPTY_ITEM_FORBIDDEN		1

#define POKEBALLS_ALLOWED			2
#define REGULAR_ITEMS_ALLOWED		4 // This includes PokéSnacks and Time flutes
#define BERRIES_ALLOWED				8
#define TMS_ALLOWED					16
#define KEY_ITEMS_ALLOWED			32
#define COLOGNES_ALLOWED			64
#define BATTLE_CDS_ALLOWED			128

#define GIVABLE_ITEMS_ALLOWED		30	// (2|4|8|16)

class ItemComboBox : public QComboBox {
public:
	ItemComboBox(unsigned int inFlags = 0, bool isXD = false, QWidget* parent = NULL);
	~ItemComboBox(void);

	void resetItemList(void);
	LibPkmGC::ItemIndex currentItemIndex(void) const;
	void setCurrentItemIndex(LibPkmGC::ItemIndex index);

	unsigned int flags(void) const;
	void setFlags(unsigned int inFlags = 0);
	
	bool version(void) const;
	void setVersion(bool isXD);

	void set(unsigned int inFlags, bool isXD);
private:
	LibPkmGC::ItemIndex* _indices;
	int* _reverseIndices;
	unsigned int _flags;
	bool _isXD;

};

#endif