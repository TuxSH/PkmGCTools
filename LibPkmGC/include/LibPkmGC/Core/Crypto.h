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