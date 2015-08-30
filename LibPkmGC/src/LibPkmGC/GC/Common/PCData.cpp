#include <LibPkmGC/GC/Common/PCData.h>

namespace LibPkmGC {
namespace GC {

PCData::PCData(size_t inSize, size_t nb_boxes, const u8* inData) : Base::DataStruct(inSize, inData), nbBoxes(nb_boxes) {
}


void PCData::deleteFields(void) {
	for (size_t i = 0; i < nbBoxes; ++i)
		delete boxes[i];
	delete[] boxes;
}

PCData::~PCData(void) {
	PCData::deleteFields();
}

PCData::PCData(PCData const& other) : Base::DataStruct(other), nbBoxes(other.nbBoxes) {
	boxes = new PokemonBox*[nbBoxes];
	CL_ARRAY(boxes, nbBoxes);
	CP_ARRAY(items, 235);
}

void PCData::swap(PCData& other) {
	if (nbBoxes != other.nbBoxes) throw std::invalid_argument("this->nbBoxes != other.nbBoxes");
	Base::DataStruct::swap(other);
	SW(boxes);
	SW_ARRAY(items, 235);
}

PCData& PCData::operator=(PCData const& other) {
	if (nbBoxes != other.nbBoxes) throw std::invalid_argument("this->nbBoxes != other.nbBoxes");
	Base::DataStruct::operator=(other);

	if (this != &other) {
		PCData::deleteFields();

		boxes = new PokemonBox*[nbBoxes];
		CL_ARRAY(boxes, nbBoxes);
		CP_ARRAY(items, 235);
	}
	return *this;
}

}
}