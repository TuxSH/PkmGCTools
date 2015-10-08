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

#ifndef _LIBPKMGC_LCRNG32_UTILITIES_H
#define _LIBPKMGC_LCRNG32_UTILITIES_H

#include <LibPkmGC/Core/IntegerTypes.h>

#include <boost/mpl/if.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/preprocessor/iteration/local.hpp>

#ifdef _MSC_VER
#	pragma warning( push )
#	pragma warning( disable : 4146 )
#	pragma warning( disable : 4307 )
#endif

namespace {
using LibPkmGC::u32;

template<u32 n> struct squared {
	static const u32 result = n*n;
};

template<u32 _a, u32 _b> struct u32_pair {
	static const u32 a = _a, b = _b;
};

template<typename T> struct self_applied {
	typedef u32_pair<T::a * T::a, T::b*(1 + T::a)> result_type;
};

template<typename T, u32 a0, u32 b0> struct advanced_once {
	typedef u32_pair<a0 * T::a, T::b * a0 + b0> result_type;
};

template<u32 a0, u32 b0, u32 a, u32 b, u32 n> struct advanced_of32_impl {
	// i.e u(n+1) = a*u(n) + b (mod 2^32)

	// Base on the rapid exponentiation method: O(log n)
	template<u32 _n, u32 nm2 = 0> struct next {
		typedef typename self_applied<typename advanced_of32_impl<a0, b0, a, b, _n / 2>::result_type>::result_type result_type;
	};

	template<u32 _n > struct next<_n, 1> {
		typedef typename advanced_once<typename advanced_of32_impl<a0, b0, a, b, _n - 1>::result_type, a0, b0>::result_type result_type;
	};

	typedef typename next<n, n % 2>::result_type result_type;
};

template<u32 a0, u32 b0, u32 _a, u32 _b> struct advanced_of32_impl<a0, b0, _a, _b, 0> {
	typedef advanced_of32_impl<a0, b0, _a, _b, 0> type;
	typedef u32_pair<1, 0> result_type;
};

}

namespace LibPkmGC {

namespace Detail {

template<u32 a, u32 n> struct pow32 {
	// Rapid exponentiation method: O(log n)
private:
	template<u32 _a, u32 _n, u32 nm2 = 0> struct next {
		static const u32 result = squared<pow32<a, n / 2>::result>::result;
	};
	template<u32 _a, u32 _n> struct next<_a, _n, 1> {
		static const u32 result = _a * pow32<_a, _n - 1>::result;
	};
public:
	static const u32 result = next<a, n, n % 2>::result;
};

template<u32 a> struct pow32<a, 0> {
	static const u32 result = 1;
};

template<u32 n> struct modularInverse32 {
	// Yields correct results iff n is odd
	// We're using Euler's theorem here in order to find the modular inverse of n mod 2^32
	static const u32 result = pow32<n, 0x7fffffff>::result;
};


template<u32 _a, u32 _b, u32 _n> struct advancedLCRNG32 {
private:
	typedef typename advanced_of32_impl<_a, _b, _a, _b, _n>::result_type R;
public:
	static const u32 a = R::a, b = R::b;
};

}

#ifndef LIBPKMGC_LCRNG32_MAX_THREADS
#	define LIBPKMGC_LCRNG32_MAX_THREADS 8
#endif

#define BOOST_PP_LOCAL_LIMITS (1, LIBPKMGC_LCRNG32_MAX_THREADS)
#define BOOST_PP_LOCAL_MACRO(n) case n: {\
	typedef Detail::advancedLCRNG32<a, b, 0xffffffff / n> adv;\
	boost::random::linear_congruential_engine<u32, adv::a, adv::b, 0> rng(initialSeed);\
	for (u32 i = 1; i < n; ++i)\
		outSeeds[i] = rng.advance();\
	break;\
}\


template<u32 _a, u32 _b> struct LCRNG32 {
private:
	static const u32 inv_a = Detail::modularInverse32<_a>::result;
public:
	static const u32 a = _a, b = _b;
	typedef boost::random::linear_congruential_engine<u32, a, b, 0> forward_generator_type;
	typedef typename boost::mpl::if_c<a % 2 == 1,
		boost::random::linear_congruential_engine<u32, inv_a, (u32)(-b * inv_a), 0>,
		void
	>::type reverse_generator_type;



	bool buildParallelSeedTable(u32 initialSeed, u32 nbThreads, u32* outSeeds) {
		if (nbThreads == 0) return false;
		outSeeds[0] = initialSeed;
		switch (nbThreads) {
#include BOOST_PP_LOCAL_ITERATE()
		default: return false;
		}
	}
};

typedef LCRNG32<0x343fd, 0x269ec3> GCRNG;
}

#ifdef _MSC_VER
#	pragma warning( pop )
#endif

#endif