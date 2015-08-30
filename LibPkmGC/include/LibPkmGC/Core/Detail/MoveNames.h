#ifndef _LIBPKMGC_MOVE_NAMES_H
#define _LIBPKMGC_MOVE_NAMES_H

#include <LibPkmGC/Core/Config.h>

namespace LibPkmGC {
namespace Localization {
namespace Detail {

namespace Moves {

#define NB_NAMES 355
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