#include <LibPkmGC/XD/Common/PokemonBox.h>

namespace LibPkmGC {
namespace XD {

PokemonBox::PokemonBox(void) : GC::PokemonBox(0x170c) {
	initWithEmptyData();
}

PokemonBox::PokemonBox(const u8* inData) : GC::PokemonBox(0x170c, inData) {
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