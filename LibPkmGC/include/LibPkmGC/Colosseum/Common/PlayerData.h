#ifndef _LIBPKMGC_COLOSSEUM_PLAYER_DATA_H
#define _LIBPKMGC_COLOSSEUM_PLAYER_DATA_H

#include <LibPkmGC/GC/Common/PlayerData.h>
#include <LibPkmGC/Colosseum/Common/Pokemon.h>
#include <LibPkmGC/Colosseum/Common/BagData.h>

namespace LibPkmGC {
namespace Colosseum {

/*
	0x00 -- 0x2b: trainer name (10+1 chars) + copy
	0x2c: u16 SID
	0x2e: u16 TID
	0x30: Pokémon Party (6*0xc4)

	0x780: bag

	0xa80: u8 trainerGender
	0xa84: u32 money
	0xa88: u32 pkCoupons + copy
*/

class LIBPKMGC_DECL PlayerData :
	public GC::PlayerData
{
public:
	static const size_t size = 0xb18;
	PlayerData(void);
	PlayerData(PlayerData const& other);

	PlayerData(const u8* inData);


	~PlayerData(void);
	PlayerData* clone(void) const;
	PlayerData* create(void) const;

	void save(void);
protected:
	void loadFields(void);
private:
	PlayerData(XD::PlayerData const& other);
};

}
}

#endif
