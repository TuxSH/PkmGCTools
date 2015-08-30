#ifndef _LIBPKMGC_XD_PLAYER_DATA_H
#define _LIBPKMGC_XD_PLAYER_DATA_H

#include <LibPkmGC/GC/Common/PlayerData.h>
#include <LibPkmGC/XD/Common/Pokemon.h>
#include <LibPkmGC/XD/Common/BagData.h>

namespace LibPkmGC {
namespace XD {

/*
	0x00 -- 0x2b: trainer name (10+1 wide characters) + copy
	0x2c: u16 SID
	0x2e: u16 TID
	0x30: Pokémon Party (6*0xc4)

	0x4c8: bag

	0x8e0: u8 trainerGender
	0x8e4: u32 money
	0x8e8: u32 pkCoupons + copy
*/

class LIBPKMGC_DECL PlayerData :
	public GC::PlayerData
{
public:
	static const size_t size = 0x978;
	PlayerData(void);
	PlayerData(PlayerData const& other);
	PlayerData(const u8* inData);


	~PlayerData(void);
	PlayerData* clone(void) const;
	PlayerData* create(void) const;

	//void swap(PlayerData& other);
	void save(void);
protected:
	void loadFields(void);
private:
	PlayerData(Colosseum::PlayerData const&);
};

}
}

#endif