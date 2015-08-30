#include <LibPkmGC/Base/PokemonBox.h>

namespace LibPkmGC {
namespace Base {

PokemonBox::PokemonBox(size_t inSize, const u8* inData) : DataStruct(inSize, inData) {

}

void PokemonBox::deleteFields(void) {
	for (size_t i = 0; i < 30; ++i)
		delete pkm[i];
}

PokemonBox::PokemonBox(PokemonBox const& other) : DataStruct(other) {
	CL(name);
	CL_ARRAY(pkm, 30);
}

PokemonBox::~PokemonBox(void) {
	PokemonBox::deleteFields();
}

void PokemonBox::swap(PokemonBox& other) {
	DataStruct::swap(other);
	SW(name);
	for (size_t i = 0; i < 30; ++i) pkm[i]->swap(*other.pkm[i]);
}

PokemonBox& PokemonBox::operator=(PokemonBox const& other) {
	DataStruct::operator=(other);
	if (this != &other) {
		PokemonBox::deleteFields();
		for (size_t i = 0; i < 30; ++i) *pkm[i] = *(other.pkm[i]);
		CL(name);
	}
	return *this;
}

}
}