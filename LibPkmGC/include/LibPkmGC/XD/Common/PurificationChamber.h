#ifndef _LIBPKMGC_XD_PURIFICATION_CHAMBER_H
#define _LIBPKMGC_XD_PURIFICATION_CHAMBER_H

#include <LibPkmGC/XD/Common/Pokemon.h>
namespace LibPkmGC {
namespace XD {

/*
	0x00: XDPokemon normalPkm[4]
	0x310: XDPokemon shadowPkm
	0x3d4: u8 ??
	0x3d5 -- end: padding/trash bytes
*/

class LIBPKMGC_DECL PurificationChamber :
	public Base::DataStruct
{
public:
	static const size_t size = 0x3d8;
	PurificationChamber(void);
	PurificationChamber(const u8* inData);

	~PurificationChamber(void);

	PurificationChamber(PurificationChamber const& other);
	PurificationChamber& operator=(PurificationChamber const& other);
	void swap(PurificationChamber& other);

	PurificationChamber* clone(void) const;
	PurificationChamber* create(void) const;

	void save(void);

	Pokemon* normalPkm[4];
	Pokemon* shadowPkm;

private:
	void deleteFields(void);
	void loadFields(void);


};

}
}

#endif