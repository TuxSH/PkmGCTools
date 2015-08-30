#ifndef _LIBPKMGC_CONFIG_H
#define _LIBPKMGC_CONFIG_H

// _LICENSE_

#include <boost/config/warning_disable.hpp>
#include <boost/config.hpp>
#include <boost/predef.h>
#define LIBPKMGC_VERSION 1000000
#define LIBPKMGC_VERSION_MAJOR ((LIBPKMGC_VERSION / 1000000) % 1000)
#define LIBPKMGC_VERSION_MINOR ((LIBPKMGC_VERSION / 1000) % 1000)
#define LIBPKMGC_VERSION_BUILD (LIBPKMGC_VERSION % 1000)

#if defined(LIBPKMGC_DYN_LIB) && !defined(LIBPKMGC_STATIC_LIB) 
#	ifdef LIBPKMGC_SOURCE
#		define LIBPKMGC_DECL BOOST_SYMBOL_EXPORT
#	else
#		define LIBPKMGC_DECL BOOST_SYMBOL_IMPORT
#	endif
#else
#	define LIBPKMGC_DECL
#endif

#endif