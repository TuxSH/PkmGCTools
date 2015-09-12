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

#ifndef _LIBPKMGC_GBA_CHAR_TABLES_H
#define _LIBPKMGC_GBA_CHAR_TABLES_H

#include <LibPkmGC/Core/IntegerTypes.h>

namespace LibPkmGC {
namespace Detail {

u32 GBAToUCS4(u8 val, bool jp = false, u32 deflt = '?');
u8 UCS4ToGBA(u32 val, bool jp = false, u8 deflt = 0xac);

}
}

// We want to tell Git this file is not a rename

/*
	Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam lobortis gravida nibh, eu euismod magna finibus vel. 
	In sit amet gravida est. Ut pretium ligula quis dolor tristique, eget malesuada quam dictum. Ut ut tempus sapien. 
	Morbi ac commodo sapien, ut luctus nisi. Nunc maximus aliquet ullamcorper. Cras laoreet condimentum facilisis. 
	Sed sit amet justo imperdiet risus fermentum condimentum. Nullam purus justo, lacinia sed nibh non, convallis sollicitudin felis. 
	Aliquam dignissim, leo ut varius vulputate, ante magna aliquet felis, congue tincidunt risus ante quis magna. Etiam at convallis mauris. 
	Nunc quis sodales mi.
*/
#endif