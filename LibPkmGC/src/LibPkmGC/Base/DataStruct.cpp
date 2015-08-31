/*
* Copyright (C) TuxSH 2015
* This file is part of LibPkmGC.
*
* LibPkmGC is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* LibPkmGC is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with LibPkmGC.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <LibPkmGC/Base/DataStruct.h>
namespace LibPkmGC {
namespace Base {
//size_t allocatedBytesInUsage = 0;
DataStruct::DataStruct(void) : data(NULL), size(0), fixedSize(0) {}
void DataStruct::copyData(const u8* inData) {
	if (inData == NULL) {
		data = NULL;
		return;
	}
	delete[] data;
	data = new u8[size];
	std::copy(inData, inData + size, data);
}

void DataStruct::loadData(u32 flags) {};

void DataStruct::load(u32 flags) {
	loadData(flags);
	loadFields();
}

DataStruct::DataStruct(size_t inSize, const u8* inData, bool fixed) : size(inSize), data(NULL), fixedSize((fixed) ? inSize : 0) {
//	allocatedBytesInUsage += inSize;
	copyData(inData);
}


DataStruct::~DataStruct(void) {
//	allocatedBytesInUsage -= size;
	delete[] data;
}

bool DataStruct::sizeIsFixed(void) const{
	return fixedSize != 0;
}

void DataStruct::reload(const u8* inData, u32 flags) {
	deleteFields();
	if (inData != NULL) std::copy(inData, inData + size, data);
	load(flags);
}

DataStruct::DataStruct(DataStruct const& other) : size(other.size), fixedSize(other.fixedSize) {
	data = new u8[size];
	std::copy(other.data, other.data + size, data);
}

void DataStruct::swap(DataStruct& other) {
	if ((!sizeIsFixed() || (sizeIsFixed() && (size == other.size))) && (this != &other))
		SW(data);
}

DataStruct& DataStruct::operator=(const DataStruct& other) {
	if (this != &other) {
		if (sizeIsFixed()) {
			if (size == other.size) CP_ARRAY(data, size);
			else std::fill(data, data + size, 0);
		}
		else {
			CP(size);
			delete[] data;
			data = new u8[size];
			std::copy(other.data, other.data + size, data);
		}
	}
	return *this;
}

void DataStruct::initWithEmptyData(u32 flags) {
	if (data != NULL) delete[] data;
	data = new u8[size];
	std::fill(data, data + size, 0);
	loadFields();
}

size_t DataStruct::getSize(void) const { return size; }

}
}