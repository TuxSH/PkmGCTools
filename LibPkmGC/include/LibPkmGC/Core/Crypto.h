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

#ifndef _LIBPKMGC_CRYPTO_H
#define _LIBPKMGC_CRYPTO_H

#include <LibPkmGC/Core/IntegerTypes.h>
#include <string>

namespace LibPkmGC {
namespace Crypto {

LIBPKMGC_DECL void sha1(const u8* start, const u8* end, u8 digest[20]);
LIBPKMGC_DECL std::string sha1(const u8* data, const u8* end);

}
}

#endif