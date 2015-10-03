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

#ifndef _LIBPKMGC_XD_TRAINER_DATA_H
#define _LIBPKMGC_XD_TRAINER_DATA_H

#include <LibPkmGC/GC/Common/TrainerData.h>
#include <LibPkmGC/XD/Common/Pokemon.h>

namespace LibPkmGC {
namespace XD {

class LIBPKMGC_DECL TrainerData :
	public GC::TrainerData
{
public:
	static const size_t size = 0x4c8;
	TrainerData(void);
	TrainerData(TrainerData const& other);
	TrainerData(const u8* inData);
	~TrainerData(void);

	TrainerData& operator=(TrainerData const& other);

	TrainerData* clone(void) const;
	TrainerData* create(void) const;

	TrainerData(GC::TrainerData const& other);
	TrainerData(Colosseum::TrainerData const& other);
protected:
	void loadFields(void);
};

}
}

#endif