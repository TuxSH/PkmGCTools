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

#ifndef _LIBPKMGC_INTEGER_TYPES_H
#define _LIBPKMGC_INTEGER_TYPES_H

#include <LibPkmGC/Core/Config.h>
#include <boost/cstdint.hpp>

namespace LibPkmGC {

#ifndef BOOST_NO_INT64_T
typedef boost::uint64_t u64;
typedef boost::int64_t  s64;
#else
#	define LIBPKM_NO_INT64_T
#endif

typedef boost::uint32_t u32;
typedef boost::uint16_t u16;
typedef boost::uint8_t  u8;

typedef boost::int32_t s32;
typedef boost::int16_t s16;
typedef boost::int8_t  s8;

}

#endif