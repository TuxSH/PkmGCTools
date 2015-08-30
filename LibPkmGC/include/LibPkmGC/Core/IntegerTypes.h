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