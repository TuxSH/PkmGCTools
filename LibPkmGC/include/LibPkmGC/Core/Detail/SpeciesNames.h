#ifndef _LIBPKMGC_SPECIES_NAMES_H
#define _LIBPKMGC_SPECIES_NAMES_H

#include <LibPkmGC/Core/Config.h>

namespace LibPkmGC {
namespace Localization {
namespace Detail {

namespace Species {

#define NB_NAMES 388
extern const char LIBPKMGC_DECL *englishNames[NB_NAMES];
extern const char LIBPKMGC_DECL *frenchNames[NB_NAMES];
extern const char LIBPKMGC_DECL *germanNames[NB_NAMES];
extern const char LIBPKMGC_DECL *italianNames[NB_NAMES]; // english names
extern const char LIBPKMGC_DECL *spanishNames[NB_NAMES]; // english names
extern const char LIBPKMGC_DECL *japaneseNames[NB_NAMES];

extern const char **names[7];

#undef NB_NAMES

}
}
}
}

#endif