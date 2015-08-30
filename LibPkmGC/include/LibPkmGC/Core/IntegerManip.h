#ifndef _LIBPKMGC_INTEGER_MANIP_H
#define _LIBPKMGC_INTEGER_MANIP_H

#include <LibPkmGC/Core/IntegerTypes.h>

#include <algorithm>
#include <iterator>
#include <stdexcept>


namespace LibPkmGC {
namespace IntegerManip {

namespace LE {
template<typename I, typename OutputIteratorType>
void fromInteger(OutputIteratorType const& _dest, I const& _integer, size_t _integerSize = sizeof(I)) {
	OutputIteratorType dst(_dest);

	for (size_t i = 0; i < _integerSize; i++) {
		*dst = (_integer >> (8 * i)) & 0xff;
		++dst;
	}
}

template<typename I, typename IteratorType>
I toInteger(IteratorType const& _bufferIterator, size_t _integerSize = sizeof(I)) {

	I ret = I(0);
	size_t shift = 0;
	IteratorType it(_bufferIterator);
	for (; shift <= 8 * _integerSize - 8; ++it) {
		ret |= (I(*it) << shift);
		shift += 8;
	}
	return ret;
}

#include <LibPkmGC/Core/Detail/IntegerManipCode.h>


}

namespace BE {

template<typename I, typename OutputIteratorType>
void fromInteger(OutputIteratorType const& _dest, I const& _integer, size_t _integerSize = sizeof(I)) {
	OutputIteratorType dst(_dest);

	std::advance(dst, _integerSize - 1);
	size_t shift = 0;

	for (; shift < 8 * _integerSize; shift += 8) {
		*dst = (_integer >> shift) & 0xff;
		if ((shift + 8) < (8 * _integerSize)) --dst;
	}
}

template<typename I, typename IteratorType>
I toInteger(IteratorType const& _bufferIterator, size_t _integerSize = sizeof(I)) {
	I ret = I(0);

	IteratorType it(_bufferIterator);
	size_t shift = 8 * _integerSize - 8;
	for (;; ++it) {
		ret |= (I(*it) << shift);
		if (shift == 0) break;
		else shift -= 8;
	}
	return ret;
}

#include <LibPkmGC/Core/Detail/IntegerManipCode.h>

}


template<typename I>
I rotateLeft(I _value, size_t _rotate, size_t _integerSize = sizeof(I)) {

	_rotate %= 8 * _integerSize;
	//e.g n [rotate left/right] 33 is equal to n [rotate left/right] 1 if n is a 8/16/32-bit integer
	return ((_value << _rotate) | (_value >> (8 * _integerSize - _rotate)));
}

template<typename I>
I rotateRight(I _value, size_t _rotate, size_t _integerSize = sizeof(I)) {

	_rotate %= 8 * _integerSize;
	return ((_value >> _rotate) | (_value << (8 * _integerSize - _rotate)));
}

template<typename I>
I extractBits(I const& _integer, size_t _endBit, size_t _beginBit, size_t _integerSize = sizeof(I)) {

	if ((_endBit >= _integerSize * 8) || (_beginBit >= _integerSize * 8))
		throw std::out_of_range("The values of _beginBit and/or _endBit you specified are too high (more than _integerSize * 8 - 1) !");

	if (_endBit < _beginBit)
		throw std::invalid_argument("_beginBit cannot be greater than _endBit !");

	return (_integer >> _beginBit) & ((1 << (_endBit - _beginBit + 1)) - 1);
}

}
}

#endif