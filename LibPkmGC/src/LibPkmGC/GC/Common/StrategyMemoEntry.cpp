#include <LibPkmGC/GC/Common/StrategyMemoEntry.h>

namespace LibPkmGC {
namespace GC {

StrategyMemoEntry::StrategyMemoEntry(const u8* inData) : Base::DataStruct(0xc, inData) {
}

void StrategyMemoEntry::deleteFields(void) {}


StrategyMemoEntry::~StrategyMemoEntry(void) {
	StrategyMemoEntry::deleteFields();
}

void StrategyMemoEntry::swap(StrategyMemoEntry& other) {
	Base::DataStruct::swap(other);
	SW(species);
	SW(flags);
	SW(firstSID);
	SW(firstTID);
	SW(firstSID);
}

void StrategyMemoEntry::loadFields(void) {
	u16 speciesIndexTmp;
	LD_FIELD(u16, speciesIndexTmp, 0);
	LD_FIELD(u16, firstSID, 4);
	LD_FIELD(u16, firstTID, 6);
	LD_FIELD(u32, firstPID, 8);

	flags = (speciesIndexTmp >> 14);
	species = (PokemonSpeciesIndex)(speciesIndexTmp & 0x3fff);
}

void StrategyMemoEntry::save(void) {
	SV_FIELD(u16, species | (flags << 14), 0);
	SV_FIELD(u16, firstSID, 4);
	SV_FIELD(u16, firstTID, 6);
	SV_FIELD(u32, firstPID, 8);
}

bool StrategyMemoEntry::isEmpty(void) const {
	return species == NoSpecies;
}

}
}