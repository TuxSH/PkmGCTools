#ifndef _LIBPKMGC_STRUCT_MACROS_H
#define _LIBPKMGC_STRUCT_MACROS_H

#include <LibPkmGC/Core/IntegerManip.h>
#include <boost/core/enable_if.hpp>

#ifdef LIBPKMGC_SOURCE
#	define LIBPKMGC_DEFINE_IMPL_HELPER_MACROS
#endif

#ifdef LIBPKMGC_DEFINE_IMPL_HELPER_MACROS

#ifndef BUFFER_NAME
#define BUFFER_NAME data
#endif

#ifndef TARGET_ENDIANNESS
#define TARGET_ENDINANNESS BE
#endif

#define SM_H_TMP_NS_EVAL() TARGET_ENDINANNESS
#define SM_H_TMP_NS() LibPkmGC::IntegerManip::SM_H_TMP_NS_EVAL()

#define LD_FIELD(type,fld,off) fld = SM_H_TMP_NS()::toInteger<type, u8*>(BUFFER_NAME+off)
#define LD_FIELD_E(type,fld,off,etype) fld = SM_H_TMP_NS()::toEnumInteger<type, etype, u8*>(BUFFER_NAME+off)
#define LD_FIELD_B(type,fld,off) fld = SM_H_TMP_NS()::toBoolInteger<type,u8*>(BUFFER_NAME+off)
#define LD_ARRAY(type,ar,sz,off) SM_H_TMP_NS()::toArrayOfIntegers<u8*,type*>(ar, BUFFER_NAME+off, BUFFER_NAME+off+(sizeof(type)*sz))
#define LD_ARRAY_E(type,ar,sz,off,etype) SM_H_TMP_NS()::toArrayOfEnumIntegers<type,u8*,etype*>(ar, BUFFER_NAME+off, BUFFER_NAME+off+(sizeof(type)*sz))
#define LD_ARRAY_B(type,ar,sz,off) SM_H_TMP_NS()::toArrayOfBoolIntegers<type,u8*,bool*>(ar, BUFFER_NAME+off, BUFFER_NAME+off+(sizeof(type)*sz))

#define SV_FIELD(type,fld,off) SM_H_TMP_NS()::fromInteger<type, u8*>(BUFFER_NAME+off, fld)
#define SV_FIELD_E(type,fld,off,etype) SM_H_TMP_NS()::fromEnumInteger<type, etype, u8*>(BUFFER_NAME+off, fld)
#define SV_FIELD_B(type,fld,off) SM_H_TMP_NS()::fromBoolInteger<type,u8*>(BUFFER_NAME+off, fld)
#define SV_ARRAY(type,ar,sz,off) SM_H_TMP_NS()::fromArrayOfIntegers<type*, u8*>(BUFFER_NAME+off, ar, ar+sz)
#define SV_ARRAY_E(type,ar,sz,off,etype) SM_H_TMP_NS()::fromArrayOfEnumIntegers<type,etype*, u8*>(BUFFER_NAME+off, ar, ar+sz)
#define SV_ARRAY_B(type,ar,sz,off) SM_H_TMP_NS()::toArrayOfBoolIntegers<type, bool*, u8*>(BUFFER_NAME+off, ar, ar+sz)

#define LD_SUBSTRUCTURE(type, fld, off) fld = new type(data + off)
#define LD_SUBSTRUCTURE_ARRAY(type, ar, sz, off) for(size_t i__ = 0; i__ < sz; ++i__) LD_SUBSTRUCTURE(type, ar[i__], off+type::size*i__);
#define LD_SUBSTRUCTURE_ARRAY2(type, ar, sz, off) for(size_t i__ = 0; i__ < sz; ++i__) LD_SUBSTRUCTURE(type, ar[i__], off+ar[i__]->getSize()*i__);

#define SV_SUBSTRUCTURE(type, fld, off) fld->save(); std::copy(fld->data, fld->data + type::size, data + off);
#define SV_SUBSTRUCTURE2(type, fld, off) fld->save(); std::copy(fld->data, fld->data + fld->getSize(), data + off);
#define SV_SUBSTRUCTURE_ARRAY(type, ar, sz, off) for(size_t i__ = 0; i__ < sz; ++i__) { SV_SUBSTRUCTURE(type, ar[i__], off+type::size*i__); }
//#define SV_SUBSTRUCTURE_ARRAY2(type, ar, sz, off) for(size_t i__ = 0; i__ < sz; ++i__) { SV_SUBSTRUCTURE2(type, ar[i__], off+ar[i__]->getSize()*i__); }



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

#define LIBPKMGC_GEN_UNIMPLEMENTED_CONVERTER_CTOR(cls)\
Colosseum::cls::cls(XD::cls const& other) : GC::cls(Colosseum::cls::size, 0){}\
XD::cls::cls(Colosseum::cls const& other) : GC::cls(XD::cls::size, 0){}

#define LIBPKMGC_GEN_UNIMPLEMENTED_SAVE_EDITING_CONVERTER_CTOR(cls)\
Colosseum::SaveEditing::cls::cls(XD::SaveEditing::cls const& other) : GC::SaveEditing::cls(Colosseum::SaveEditing::cls::size, 0){}\
XD::SaveEditing::cls::cls(Colosseum::SaveEditing::cls const& other) : GC::SaveEditing::cls(XD::SaveEditing::cls::size, 0){}

#define LIBPKMGC_GC_GEN_XD_VTF2(cls, flgs) \
cls& cls::operator=(GC::cls const& other){\
if(LIBPKMGC_IS_XD(cls,&other)) return (cls&) operator=((cls const&)other);\
else { deleteFields(); initWithEmptyData(flgs); return (cls&) GC::cls::operator=(other); }\
}\
void cls::swap(GC::cls & other){\
if(LIBPKMGC_IS_XD(cls,&other)) swap((cls&)other);\
else {cls obj((Colosseum::cls&)other); swap(obj); other.swap(obj);}\
}

#define LIBPKMGC_GC_GEN_COL_VTF2(cls, flgs) \
cls& cls::operator=(GC::cls const& other){\
if(LIBPKMGC_IS_COLOSSEUM(cls,&other)) return operator=((cls const&)other);\
else { deleteFields(); initWithEmptyData(flgs); return (cls&) GC::cls::operator=(other); }\
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


#endif

#endif