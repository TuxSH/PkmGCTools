#ifndef _LIBPKMGC_BASE_DATASTRUCT_H
#define _LIBPKMGC_BASE_DATASTRUCT_H

#include <LibPkmGC/Core/Detail/StructMacros.h>

#define LIBPKMGC_STRUCT_DECRYPTED 1
#define LIBPKMGC_FWD_DECL_GC_CLS(cls) namespace Colosseum { class cls; } namespace XD { class cls; }


namespace LibPkmGC {
namespace Base {

class LIBPKMGC_DECL DataStruct {
public:
	u8* data;
	//u32 statusFlags;

	DataStruct(void);
	DataStruct(size_t inSize, const u8* inData = NULL, bool fixed = true);

	virtual void save(void) = 0;

	virtual void reload(const u8* inData = NULL, u32 flags = 0);

	DataStruct(const DataStruct& other);
	virtual DataStruct* clone(void) const = 0;
	virtual DataStruct* create(void) const = 0;

	void swap(DataStruct& other);
	DataStruct& operator=(DataStruct const& other);

	virtual ~DataStruct(void);

	bool sizeIsFixed(void) const;
	const size_t fixedSize; // = 0 if not fixed
	size_t getSize(void) const;
protected:
	size_t size;
	void initWithEmptyData(u32 flags = 0);

	void copyData(const u8* data = NULL);
	virtual void load(u32 flags = 0);
	virtual void loadData(u32 flags = 0);
	virtual void loadFields(void) = 0;
	virtual void deleteFields(void) = 0; // delete dynamically allocated fields
};

class LIBPKMGC_DECL UnimplementedStruct : public DataStruct {
public:
	UnimplementedStruct(void) : DataStruct() { }
	UnimplementedStruct(size_t inSize, const u8* inData = NULL) : DataStruct(inSize, inData) { if (inData == NULL) initWithEmptyData(); }

	UnimplementedStruct* clone(void) const { return new UnimplementedStruct(*this); }
	UnimplementedStruct* create(void) const { return new UnimplementedStruct; }

	void save(void) {}

private:
	void loadFields(void) {}
	void deleteFields(void) {}
};

}
}

#endif