/*
* Copyright (C) TuxSH 2015
* This file is part of LibPkmGC.
*
* LibPkmGC is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* LibPkmGC is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with LibPkmGC.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <LibPkmGC/Core/ItemInfo.h>
#include <LibPkmGC/Core/Detail/StructMacros.h>

namespace LibPkmGC {

void Item::load(u8 * data) {
	LD_FIELD_E(u16, index, 0, ItemIndex);
	LD_FIELD(u16, quantity, 2);
}

void Item::save(u8 * data) {
	SV_FIELD_E(u16, index, 0, ItemIndex);
	SV_FIELD(u16, quantity, 2);
}

ItemCategoryIndex getItemCategory(ItemIndex index, bool isXD) {
	u16 i = (u16)index;
	if ((index >= MasterBall) && (index <= PremierBall)) return PokeballsCategory;
	if ((index >= Potion) && (index <= GreenShard)) return RegularItemsCategory;
	if ((index >= HPUp) && (index <= Repel) && (i != 0x48) && (i != 0x52)) return RegularItemsCategory;
	if ((index >= SunStone) && (index <= LeafStone)) return RegularItemsCategory;
	if ((index >= TinyMushroom) && (index <= HeartScale) && (i != 0x69)) return RegularItemsCategory;
	if ((index >= OrangeMail) && (index <= RetroMail)) return RegularItemsCategory;
	if ((index >= CheriBerry) && (index <= EnigmaBerry)) return BerriesCategory;
	if ((index >= BrightPowder) && (index <= Stick)) return RegularItemsCategory;
	if ((index >= RedScarf) && (index <= YellowScarf)) return RegularItemsCategory;
	if ((index >= TM01) && (index <= TM50)) return TMsCategory;
	if (isXD) {
		if ((index >= SafeKey) && (index <= MirorRadar)) return KeyItemsCategory;
		if (index == PokeSnack) return RegularItemsCategory;
		if (index == CologneCase_XD) return KeyItemsCategory;
		if ((index >= JoyScent_XD) && (index <= VividScent_XD)) return ColognesCategory;
		if ((index >= SunShard) && (index <= CryAnalyzer)) return KeyItemsCategory;
		if ((index >= KraneMemo1) && (index <= DiscCase)) return KeyItemsCategory;
		if ((index >= BattleCD01) && (index <= BattleCD60)) return BattleCDsCategory;
	}
	else {
		if ((index >= JailKey) && (index <= YlwIDBadge)) return KeyItemsCategory;
		if (index == TimeFlute) return RegularItemsCategory;
		if ((index >= JoyScent_C) && (index <= VividScent_C)) return ColognesCategory;
		if ((index == PowerupPart) || (index == EinFileF)) return KeyItemsCategory;
	}
	return NoItemCategory;
}

}