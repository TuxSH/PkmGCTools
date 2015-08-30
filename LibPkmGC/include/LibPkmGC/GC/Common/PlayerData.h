#ifndef _LIBPKMGC_GC_PLAYER_DATA_H
#define _LIBPKMGC_GC_PLAYER_DATA_H

#include <LibPkmGC/GC/Common/Pokemon.h>
#include <LibPkmGC/GC/Common/BagData.h>

namespace LibPkmGC {

LIBPKMGC_FWD_DECL_GC_CLS(PlayerData)

namespace GC {

class LIBPKMGC_DECL PlayerData :
	public Base::DataStruct
{
public:
	PlayerData(size_t inSize, const u8* inData = NULL);
	PlayerData& operator=(PlayerData const& other);

	virtual PlayerData* clone(void) const = 0;
	virtual PlayerData* create(void) const = 0;

	virtual ~PlayerData(void);

	void swap(PlayerData& other);

	void swapPokemon(size_t n, size_t m);
	virtual void save(void);


	PokemonString* trainerName;
	u16 SID, TID;

	Pokemon* party[6];

	BagData* bag;

	Gender trainerGender;
	u32 money;
	u32 pkCoupons;
	
protected:
	PlayerData(PlayerData const& other);

	virtual void deleteFields(void);
	virtual void loadFields(void);
};

}
}

#endif