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

#ifndef _LIBPKMGC_RIBBON_DESCRIPTIONS_H
#define _LIBPKMGC_RIBBON_DESCRIPTIONS_H

#include <LibPkmGC/Core/Config.h>

namespace LibPkmGC {
namespace Localization {
namespace Detail {

namespace RibbonDescriptions {

#define NB_NAMES 65
extern const char LIBPKMGC_DECL *englishNames[NB_NAMES];
extern const char LIBPKMGC_DECL *frenchNames[NB_NAMES];
extern const char LIBPKMGC_DECL *germanNames[NB_NAMES];
extern const char LIBPKMGC_DECL *italianNames[NB_NAMES];
extern const char LIBPKMGC_DECL *spanishNames[NB_NAMES];
extern const char LIBPKMGC_DECL *japaneseNames[NB_NAMES];

extern const char **names[7];
#undef NB_NAMES

}
}
}
}

#endif