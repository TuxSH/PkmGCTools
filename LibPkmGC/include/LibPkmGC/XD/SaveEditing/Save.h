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


#ifndef _LIBPKMGC_XD_SAVE_EDITING_SAVE_H
#define _LIBPKMGC_XD_SAVE_EDITING_SAVE_H

#include <LibPkmGC/GC/SaveEditing/Save.h>
#include <LibPkmGC/XD/SaveEditing/SaveSlot.h>

namespace LibPkmGC {
namespace XD {
namespace SaveEditing {

class LIBPKMGC_DECL Save :
	public GC::SaveEditing::Save
{
public:
	static const size_t size = 0x56000;
	Save(void);
	Save(Save const& other);
	Save(const u8* inData, bool hasGCIData_ = false, bool isDecrypted = false);
	//~Save(void);

	Save* clone(void) const;
	Save* create(void) const;

	void save_impl(bool saveAll);

	void saveUnshuffled(void);

protected:
	void loadFields(void);

private:
	Save(Colosseum::SaveEditing::Save const&);
};

}
}
}

#endif