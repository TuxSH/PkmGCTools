#include <LibPkmGC/Colosseum/Common/PCData.h>

namespace LibPkmGC {
namespace Colosseum {

PCData::PCData(void) : GC::PCData(0x7198, 3) {
	initWithEmptyData();
}

PCData::PCData(const u8* inData) : GC::PCData(0x7198, 3, inData) {
	load();
}

PCData::PCData(PCData const& other) : GC::PCData(other) {}
PCData::~PCData(void) {
}

PCData* PCData::clone(void) const {
	return new PCData(*this);
}

PCData* PCData::create(void) const {
	return new PCData;
}


void PCData::loadFields(void) {
	boxes = new GC::PokemonBox*[nbBoxes];

	LD_SUBSTRUCTURE_ARRAY(PokemonBox, boxes, 3, 0);

	for (size_t i = 0; i < 235; ++i)
		items[i].load(data + 0x6dec + 4*i);
}

void PCData::save(void) {
	SV_SUBSTRUCTURE_ARRAY(PokemonBox, boxes, 3, 0);

	for (size_t i = 0; i < 235; ++i)
		items[i].save(data + 0x6dec + 4*i);
}

}
}