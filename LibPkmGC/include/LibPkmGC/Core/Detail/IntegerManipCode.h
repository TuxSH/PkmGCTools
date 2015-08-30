template<typename I, typename E, typename OutputIteratorType>
void fromEnumInteger(OutputIteratorType const& _dest, E const& _integer, size_t _integerSize = sizeof(I)){
	return fromInteger<I,OutputIteratorType>(_dest, (I) _integer, _integerSize);
}

template<typename I, typename E, typename IteratorType>
E toEnumInteger(IteratorType const& _bufferIterator, size_t _integerSize = sizeof(I)){
	return (E) toInteger<I,IteratorType>(_bufferIterator, _integerSize);
}


template<typename I, typename OutputIteratorType>
void fromBoolInteger(OutputIteratorType const& _dest, bool _integer, size_t _integerSize = sizeof(I)){
	return fromInteger<I,OutputIteratorType>(_dest, (I) (_integer) ? 1 : 0, _integerSize);
}

template<typename I, typename IteratorType>
bool toBoolInteger(IteratorType const& _bufferIterator, size_t _integerSize = sizeof(I)){
	return toInteger<I,IteratorType>(_bufferIterator, _integerSize) != 0;
}

template<typename IteratorType, typename OutputIteratorType>
void fromArrayOfIntegers(OutputIteratorType const& _dest, IteratorType const& _integers, 
                         IteratorType const& _integersEnd,
                         size_t _integerSize = sizeof(typename std::iterator_traits<IteratorType>::value_type)){

    typedef typename std::iterator_traits<IteratorType>::value_type I;

	size_t _count = std::distance(_integers, _integersEnd);

	IteratorType it(_integers);
	OutputIteratorType dst(_dest);

	for(size_t i = 0; i < _count; i++){
        fromInteger<I,OutputIteratorType>(dst, *it, _integerSize);
		++it;
		std::advance(dst, _integerSize);
	}
}

template<typename I, typename IteratorType, typename OutputIteratorType>
void fromArrayOfEnumIntegers(OutputIteratorType const& _dest, IteratorType const& _integers, 
                         IteratorType const& _integersEnd,
                         size_t _integerSize = sizeof(I)){

    typedef typename std::iterator_traits<IteratorType>::value_type E;
	size_t _count = std::distance(_integers, _integersEnd);

	IteratorType it(_integers);
	OutputIteratorType dst(_dest);

	for(size_t i = 0; i < _count; i++){
        fromEnumInteger<I,E,OutputIteratorType>(dst, *it, _integerSize);
		++it;
		std::advance(dst, _integerSize);
	}
}

template<typename I, typename IteratorType, typename OutputIteratorType>
void fromArrayOfBoolIntegers(OutputIteratorType const& _dest, IteratorType const& _integers, 
                         IteratorType const& _integersEnd,
                         size_t _integerSize = sizeof(I)){

	size_t _count = std::distance(_integers, _integersEnd);

	IteratorType it(_integers);
	OutputIteratorType dst(_dest);

	for(size_t i = 0; i < _count; i++){
        fromBoolInteger<I,OutputIteratorType>(dst, *it, _integerSize);
		++it;
		std::advance(dst, _integerSize);
	}
}

template<typename IteratorType, typename OutputIteratorType>
void toArrayOfIntegers(OutputIteratorType const& _dest, IteratorType const& _bufferIterator, 
                       IteratorType const& _bufferIteratorEnd,
                       size_t _integerSize = sizeof(typename std::iterator_traits<OutputIteratorType>::value_type)){
//	size_t _count = std::distance(_bufferIterator, bufferIteratorEnd);
    typedef typename std::iterator_traits<OutputIteratorType>::value_type I;

	IteratorType it2(_bufferIterator);
	OutputIteratorType dst(_dest);

	for(; it2 != _bufferIteratorEnd; std::advance(it2, _integerSize)){
        *dst = toInteger<I, IteratorType>(it2, _integerSize);
		++dst;
	}
}

template<typename I, typename IteratorType, typename OutputIteratorType>
void toArrayOfEnumIntegers(OutputIteratorType const& _dest, IteratorType const& _bufferIterator, 
                       IteratorType const& _bufferIteratorEnd,
                       size_t _integerSize = sizeof(I)){
//	size_t _count = std::distance(_bufferIterator, bufferIteratorEnd);
    typedef typename std::iterator_traits<OutputIteratorType>::value_type E;

	IteratorType it2(_bufferIterator);
	OutputIteratorType dst(_dest);

	for(; it2 != _bufferIteratorEnd; std::advance(it2, _integerSize)){
        *dst = toEnumInteger<I, E, IteratorType>(it2, _integerSize);
		++dst;
	}
}

template<typename I, typename IteratorType, typename OutputIteratorType>
void toArrayOfBoolIntegers(OutputIteratorType const& _dest, IteratorType const& _bufferIterator, 
                       IteratorType const& _bufferIteratorEnd,
                       size_t _integerSize = sizeof(I)){
//	size_t _count = std::distance(_bufferIterator, bufferIteratorEnd);
	IteratorType it2(_bufferIterator);
	OutputIteratorType dst(_dest);

	for(; it2 != _bufferIteratorEnd; std::advance(it2, _integerSize)){
        *dst = toBoolInteger<I, IteratorType>(it2, _integerSize);
		++dst;
	}
}