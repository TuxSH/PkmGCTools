#include <LibPkmGC/Colosseum/Common/PokemonBox.h>

namespace LibPkmGC {
namespace Colosseum {

PokemonBox::PokemonBox(void) : GC::PokemonBox(0x24a4) {
	initWithEmptyData();
}

PokemonBox::PokemonBox(const u8* inData) : GC::PokemonBox(0x24a4, inData) {
	load();
}
PokemonBox::PokemonBox(PokemonBox const& other) : GC::PokemonBox(other) {}


PokemonBox::~PokemonBox(void)
{
}



PokemonBox* PokemonBox::clone(void) const {
	return new PokemonBox(*this);
}

PokemonBox* PokemonBox::create(void) const {
	return new PokemonBox;
}



void PokemonBox::loadFields(void) {
	GC::PokemonBox::loadFields();
	LD_SUBSTRUCTURE_ARRAY(Pokemon, pkm, 30, 0x14);
}

void PokemonBox::save(void) {
	GC::PokemonBox::save();
	SV_SUBSTRUCTURE_ARRAY(Pokemon, pkm, 30, 0x14);
}

}
}