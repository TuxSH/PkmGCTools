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

#ifndef _LIBPKMGC_STRUCT_MACROS_H
#define _LIBPKMGC_STRUCT_MACROS_H

#include <LibPkmGC/Core/IntegerManip.h>

#include <boost/version.hpp>
#if BOOST_VERSION < 105600 
#	include <boost/utility/enable_if.hpp> // < 1.56
#else
#	include <boost/core/enable_if.hpp>
#endif

#ifdef LIBPKMGC_SOURCE
#	define LIBPKMGC_DEFINE_IMPL_HELPER_MACROS
#endif

#ifdef LIBPKMGC_DEFINE_IMPL_HELPER_MACROS

#ifndef BUFFER_NAME
#define BUFFER_NAME data
#endif
/*
#ifndef TARGET_ENDIANNESS
#define TARGET_ENDINANNESS BE
#endif
*/

using namespace LibPkmGC::IntegerManip;
#if !defined(TARGET_ENDIANNESS_LE) 
using namespace BE;
#else
using namespace LE;
#endif

#define LD_FIELD(type,fld,off) fld = toInteger<type, u8*>(BUFFER_NAME+off)
#define LD_FIELD_MAX(type,fld,off,mx) fld = toInteger<type, u8*>(BUFFER_NAME+off); fld = (fld > mx) ? mx : fld
#define LD_FIELD_CONV(type,fld,off,type2) type fld##_tmp; LD_FIELD_MAX(type,fld##_tmp,off,(type2)-1); fld = (type2) fld##_tmp;
#define LD_FIELD_E(type,fld,off,etype) fld = toEnumInteger<type, etype, u8*>(BUFFER_NAME+off)
#define LD_FIELD_E_MAX(type,fld,off,etype,mx) fld = toEnumInteger<type, etype, u8*>(BUFFER_NAME+off); fld = ((u32)fld > (u32)mx) ? (etype)0 : fld
#define LD_FIELD_B(type,fld,off) fld = toBoolInteger<type,u8*>(BUFFER_NAME+off)
#define LD_ARRAY(type,ar,sz,off) toArrayOfIntegers<u8*,type*>(ar, BUFFER_NAME+off, BUFFER_NAME+off+(sizeof(type)*sz))
#define LD_ARRAY_MAX(type,ar,sz,off,mx) toArrayOfIntegers<u8*,type*>(ar, BUFFER_NAME+off, BUFFER_NAME+off+(sizeof(type)*sz));\
for(size_t i__ = 0; i__ < sz; ++i__) ar[i__] = (ar[i__] > mx) ? mx : ar[i__];
#define LD_ARRAY_CONV(type,ar,sz,off,type2) type ar##_tmp[sz]; toArrayOfIntegers<u8*,type*>(ar##_tmp, BUFFER_NAME+off, BUFFER_NAME+off+(sizeof(type)*sz));\
for(size_t i__ = 0; i__ < sz; ++i__) ar[i__] = (type2)((ar##_tmp[i__] > (type2)-1) ? (type2)-1 : ar##_tmp[i__]);
#define LD_ARRAY_E(type,ar,sz,off,etype) toArrayOfEnumIntegers<type,u8*,etype*>(ar, BUFFER_NAME+off, BUFFER_NAME+off+(sizeof(type)*sz))
#define LD_ARRAY_E_MAX(type,ar,sz,off,etype,mx) toArrayOfEnumIntegers<type,u8*,etype*>(ar, BUFFER_NAME+off, BUFFER_NAME+off+(sizeof(type)*sz));\
for(size_t i__ = 0; i__ < sz; ++i__) ar[i__] = ((u32)ar[i__] > (u32)mx) ? (etype)0 : ar[i__];
#define LD_ARRAY_B(type,ar,sz,off) toArrayOfBoolIntegers<type,u8*,bool*>(ar, BUFFER_NAME+off, BUFFER_NAME+off+(sizeof(type)*sz))
#define LD_BIT_ARRAY2(type,ar,sz,off,st) type ar##_tmp; LD_FIELD(type, ar##_tmp, off); for(int i__ = 0; i__ < sz; ++i__) ar[i__] = (ar##_tmp & (1U << (8*sizeof(type) - 1 - st - i__))) != 0;
#define LD_BIT_ARRAY(type, ar, sz, off)  LD_BIT_ARRAY2(type,ar,sz,off,0)

#define SV_FIELD(type,fld,off) fromInteger<type, u8*>(BUFFER_NAME+off, fld)
#define SV_FIELD_MAX(type,fld,off,mx) fld = (fld > mx) ? mx : fld; fromInteger<type, u8*>(BUFFER_NAME+off, fld)
#define SV_FIELD_CONV(type,fld,off,type2) fld = (fld > (type2)-1) ? (type2)-1 : fld; fromInteger<type, u8*>(BUFFER_NAME+off, (type)fld)
#define SV_FIELD_E(type,fld,off,etype) fromEnumInteger<type, etype, u8*>(BUFFER_NAME+off, fld)
#define SV_FIELD_E_MAX(type,fld,off,etype,mx) fld = ((u32)fld > (u32)mx) ? (etype)0 : fld; fromEnumInteger<type, etype, u8*>(BUFFER_NAME+off, fld)
#define SV_FIELD_B(type,fld,off) fromBoolInteger<type,u8*>(BUFFER_NAME+off, fld)
#define SV_ARRAY(type,ar,sz,off) fromArrayOfIntegers<type*, u8*>(BUFFER_NAME+off, ar, ar+sz)
#define SV_ARRAY_MAX(type,ar,sz,off,mx) for(size_t i__ = 0; i__ < sz; ++i__) ar[i__] = (ar[i__] > mx) ? mx : ar[i__];\
fromArrayOfIntegers<type*, u8*>(BUFFER_NAME+off, ar, ar+sz)
#define SV_ARRAY_CONV(type,ar,sz,off,type2) type ar##_tmp[sz]; for(size_t i__=0;i__<sz;++i__) ar##_tmp[i__] = ((ar[i__] > (type)-1) ? (type)-1 : (type) ar[i__]);\
fromArrayOfIntegers<type*, u8*>(BUFFER_NAME+off, ar##_tmp, ar##_tmp+sz)
#define SV_ARRAY_E(type,ar,sz,off,etype) fromArrayOfEnumIntegers<type,etype*, u8*>(BUFFER_NAME+off, ar, ar+sz)
#define SV_ARRAY_E_MAX(type,ar,sz,off,etype,mx) for(size_t i__ = 0; i__ < sz; ++i__) ar[i__] = ((u32)ar[i__] > (u32)mx) ? (etype)0 : ar[i__];\
fromArrayOfEnumIntegers<type,etype*, u8*>(BUFFER_NAME+off, ar, ar+sz)
#define SV_ARRAY_B(type,ar,sz,off) toArrayOfBoolIntegers<type, bool*, u8*>(BUFFER_NAME+off, ar, ar+sz)
#define SV_BIT_ARRAY2(type, ar, sz, off, st) type ar##_tmp; LD_FIELD(type, ar##_tmp, off); ar##_tmp &= ~(((1U << sz) - 1) << (8*sizeof(type) - 1 - st - sz));\
for(int i__ = 0; i__ < sz; ++i__) ar##_tmp |= ((ar[i__]) ? 1U : 0U) << (8*sizeof(type) - 1 - st - i__); SV_FIELD(type, ar##_tmp, off); 
#define SV_BIT_ARRAY(type, ar, sz, off)  SV_BIT_ARRAY2(type,ar,sz,off,0)


#define LD_SUBSTRUCTURE(type, fld, off) fld = new type(data + off)
#define LD_SUBSTRUCTURE_ARRAY(type, ar, sz, off) for(size_t i__ = 0; i__ < sz; ++i__) LD_SUBSTRUCTURE(type, ar[i__], off+type::size*i__);
#define LD_SUBSTRUCTURE_ARRAY2(type, ar, sz, off) for(size_t i__ = 0; i__ < sz; ++i__) LD_SUBSTRUCTURE(type, ar[i__], off+ar[i__]->getSize()*i__);

#define SV_SUBSTRUCTURE(type, fld, off) fld->save(); std::copy(fld->data, fld->data + type::size, data + off);
#define SV_SUBSTRUCTURE2(type, fld, off) fld->save(); std::copy(fld->data, fld->data + fld->getSize(), data + off);
#define SV_SUBSTRUCTURE_ARRAY(type, ar, sz, off) for(size_t i__ = 0; i__ < sz; ++i__) { SV_SUBSTRUCTURE(type, ar[i__], off+type::size*i__); }



#define CP(fld) this->fld = other.fld
#define CP_ARRAY(fld, sz) std::copy(other.fld, other.fld+sz, fld)

#define SW(fld) std::swap(this->fld, other.fld)
#define SW_ARRAY(fld, sz) for(size_t i__0123 = 0; i__0123 < sz; ++i__0123) SW(fld[i__0123]);

#define ASSIGN_CP(fld) *(this->fld) = *(other.fld)
#define ASSIGN_ARRAY_CP(fld, sz) for(size_t i__1234 = 0; i__1234 < sz; ++i__1234) ASSIGN_CP(fld[i__1234]);

#define CL(fld) this->fld = other.fld->clone();
#define CL_ARRAY(fld, sz) for(size_t i__1234 = 0; i__1234 < sz; ++i__1234) CL(fld[i__1234]);

#define LIBPKMGC_GEN_CONVERTER_CTOR2(cls, flgs) \
Colosseum::cls::cls(XD::cls const& other) : GC::cls(Colosseum::cls::size){\
	initWithEmptyData(flgs);\
	GC::cls::operator=(other);\
}\
XD::cls::cls(Colosseum::cls const& other) : GC::cls(XD::cls::size){\
	initWithEmptyData(flgs);\
	GC::cls::operator=(other);\
}

#define LIBPKMGC_GEN_CONVERTER_CTOR(cls) LIBPKMGC_GEN_CONVERTER_CTOR2(cls, 0)

#define LIBPKMGC_GEN_CONVERTER_CTOR_W_GBA(cls) LIBPKMGC_GEN_CONVERTER_CTOR(cls)\
XD::cls::cls(GBA::cls const& other) : GC::cls(XD::cls::size){\
	initWithEmptyData(0);\
	GC::cls::operator=(other);\
}\
Colosseum::cls::cls(GBA::cls const& other) : GC::cls(XD::cls::size){\
	initWithEmptyData(0);\
	GC::cls::operator=(other);\
}

#define LIBPKMGC_GC_GEN_XD_VTF2(cls, flgs) \
cls& cls::operator=(GC::cls const& other){\
if(LIBPKMGC_IS_XD(cls,&other)) return (cls&) operator=((cls const&)other);\
else { 	if (this == &other) return *this; deleteFields(); initWithEmptyData(flgs); return (cls&) GC::cls::operator=(other); }\
}\
void cls::swap(GC::cls & other){\
if(LIBPKMGC_IS_XD(cls,&other)) swap((cls&)other);\
else {cls obj((Colosseum::cls&)other); swap(obj); other.swap(obj);}\
}

#define LIBPKMGC_GC_GEN_COL_VTF2(cls, flgs) \
cls& cls::operator=(GC::cls const& other){\
if(LIBPKMGC_IS_COLOSSEUM(cls,&other)) return operator=((cls const&)other);\
else { 		if (this == &other) return *this; deleteFields(); initWithEmptyData(flgs); return (cls&) GC::cls::operator=(other); }\
}\
void cls::swap(GC::cls & other){\
if(LIBPKMGC_IS_COLOSSEUM(cls,&other)) swap((cls&)other);\
else {cls obj((XD::cls&)other); swap(obj); other.swap(obj);}\
}

#define LIBPKMGC_GC_GEN_XD_VTF(cls) LIBPKMGC_GC_GEN_XD_VTF2(cls,0)
#define LIBPKMGC_GC_GEN_COL_VTF(cls) LIBPKMGC_GC_GEN_COL_VTF2(cls, 0)
#endif 

#ifndef BOOST_NO_SFINAE

namespace {
#define CREATE_MEMBER_DETECTOR(X)                                                   \
template<typename T> class Detect_##X {                                             \
    struct Fallback { int X; };                                                     \
    struct Derived : T, Fallback { };                                               \
                                                                                    \
    template<typename U, U> struct Check;                                           \
                                                                                    \
    typedef char ArrayOfOne[1];                                                     \
    typedef char ArrayOfTwo[2];                                                     \
                                                                                    \
    template<typename U> static ArrayOfOne & func(Check<int Fallback::*, &U::X> *); \
    template<typename U> static ArrayOfTwo & func(...);                             \
  public:                                                                           \
    typedef Detect_##X type;                                                        \
    static const bool value = sizeof(func<Derived>(0)) == 2;                                 \
};

CREATE_MEMBER_DETECTOR(isXD)
#undef CREATE_MEMBER_DETECTOR
 
}

namespace LibPkmGC {
namespace Detail {
template<typename T> bool test_isXD_or_true(T* obj, typename boost::disable_if<Detect_isXD<T> >::type* dummy = NULL) { return true; }
template<typename T> bool test_isXD_or_true(T* obj, typename boost::enable_if<Detect_isXD<T> >::type* dummy = NULL) {
	return obj->isXD();
}
}
}



#define LIBPKMGC_IS_XD(cls, obj) ((obj)->fixedSize == LibPkmGC::XD::cls::size && LibPkmGC::Detail::test_isXD_or_true(obj))
#define LIBPKMGC_IS_COLOSSEUM(cls, obj) ((obj)->fixedSize == LibPkmGC::Colosseum::cls::size && LibPkmGC::Detail::test_isXD_or_true(obj))
#define LIBPKMGC_IS_GBA(cls, obj) ((obj)->fixedSize == LibPkmGC::GBA::cls::size) 

#endif

#endif