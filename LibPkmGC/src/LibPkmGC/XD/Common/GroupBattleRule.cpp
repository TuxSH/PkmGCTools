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

#include <LibPkmGC/XD/Common/GroupBattleRule.h>

namespace LibPkmGC {
namespace XD {

GroupBattleRule::GroupBattleRule(const u8* inData) : GC::GroupBattleRule(0x90, 62, inData) {
	load();
}

GroupBattleRule::GroupBattleRule(void) : GC::GroupBattleRule(0x90, 62) {
	initWithEmptyData();
}

GroupBattleRule::GroupBattleRule(GroupBattleRule const& other) : GC::GroupBattleRule(other), revealDeoxysForm(other.revealDeoxysForm),
nbPkm(other.nbPkm), isBattleOpen(other.isBattleOpen) {
	CL(customName);
}

void GroupBattleRule::deleteFields(void) {
	delete customName;
}

GroupBattleRule::~GroupBattleRule() {
	GroupBattleRule::deleteFields();
}

void GroupBattleRule::swap(GroupBattleRule & other) {
	GC::GroupBattleRule::swap(other);
	SW(nbPkm);
	SW(isBattleOpen);
	SW(revealDeoxysForm);
	SW(customName);
}

GroupBattleRule* GroupBattleRule::clone(void) const {
	return new GroupBattleRule(*this);
}

GroupBattleRule* GroupBattleRule::create(void) const {
	return new GroupBattleRule;
}

void GroupBattleRule::loadFields(void) {
	GC::GroupBattleRule::loadFields();
	LD_FIELD_B(u8, revealDeoxysForm, 25);
	LD_FIELD(u16, nbPkm, 26);
	LD_FIELD_B(u16, isBattleOpen, 28);
	customName = new GC::PokemonString(data + 30, 25); // (25+1)*2 bytes
	LD_ARRAY_B(u8, bannedItems, 62, 82);

}

void GroupBattleRule::save(void) {
	GC::GroupBattleRule::save();
	SV_FIELD_B(u8, revealDeoxysForm, 25);
	SV_FIELD(u16, nbPkm, 26);
	SV_FIELD_B(u16, isBattleOpen, 28);
	customName->save(data + 30, 25);
	SV_ARRAY_B(u8, bannedItems, 62, 82);
}

}
}