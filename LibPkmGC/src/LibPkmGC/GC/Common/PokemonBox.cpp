#include <LibPkmGC/GC/Common/PokemonBox.h>

namespace LibPkmGC {
namespace GC {

PokemonBox::PokemonBox(size_t inSize, const u8* inData) : Base::PokemonBox(inSize, inData){
};

PokemonBox::~PokemonBox(void) {
}

PokemonBox::PokemonBox(PokemonBox const& other) : Base::PokemonBox(other) {

}
void PokemonBox::loadFields(void) {
	name = new PokemonString(data, 8);
}

void PokemonBox::save(void) {
	name->save(data, 8);
}

}
}