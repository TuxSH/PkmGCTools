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

#ifndef _LIBPKMGC_CONFIG_H
#define _LIBPKMGC_CONFIG_H

#include <boost/config/warning_disable.hpp>
#include <boost/config.hpp>

#define LIBPKMGC_VERSION 1002000
#define LIBPKMGC_VERSION_MAJOR ((LIBPKMGC_VERSION / 1000000) % 1000)
#define LIBPKMGC_VERSION_MINOR ((LIBPKMGC_VERSION / 1000) % 1000)
#define LIBPKMGC_VERSION_BUILD (LIBPKMGC_VERSION % 1000)

#if defined(LIBPKMGC_DYN_LIB)
#	ifdef LIBPKMGC_SOURCE
#		define LIBPKMGC_DECL BOOST_SYMBOL_EXPORT
#	else
#		define LIBPKMGC_DECL BOOST_SYMBOL_IMPORT
#	endif
#else
#	define LIBPKMGC_DECL
#endif

#endif