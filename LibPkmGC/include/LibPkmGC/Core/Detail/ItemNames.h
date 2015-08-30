#ifndef _LIBPKMGC_ITEM_NAMES_H
#define _LIBPKMGC_ITEM_NAMES_H


#include <LibPkmGC/Core/Config.h>

namespace LibPkmGC {
namespace Localization {
namespace Detail {

namespace GivableItems {

#define NB_NAMES 245
extern const char LIBPKMGC_DECL *englishNames[NB_NAMES];
extern const char LIBPKMGC_DECL *frenchNames[NB_NAMES];
extern const char LIBPKMGC_DECL *germanNames[NB_NAMES];
extern const char LIBPKMGC_DECL *italianNames[NB_NAMES];
extern const char LIBPKMGC_DECL *spanishNames[NB_NAMES];
extern const char LIBPKMGC_DECL *japaneseNames[NB_NAMES];

extern const char **names[7];
#undef NB_NAMES

}

namespace ColosseumExclusiveItems { // Some items are common to Col. and XD

#define NB_NAMES 48
extern const char LIBPKMGC_DECL *englishNames[NB_NAMES];
extern const char LIBPKMGC_DECL *frenchNames[NB_NAMES];
extern const char LIBPKMGC_DECL *germanNames[NB_NAMES];
extern const char LIBPKMGC_DECL *italianNames[NB_NAMES];
extern const char LIBPKMGC_DECL *spanishNames[NB_NAMES];
extern const char LIBPKMGC_DECL *japaneseNames[NB_NAMES];

extern const char **names[7];

#undef NB_NAMES

}

namespace XDExclusiveItems {

extern const size_t namesByIndex[94];
// BEWARE, these ones are not in the correct order
#define NB_NAMES 91
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