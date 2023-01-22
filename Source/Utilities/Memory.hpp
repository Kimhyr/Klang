#ifndef KLANG_UTILITIES_MEMORY_HPP
#define KLANG_UTILITIES_MEMORY_HPP

#include "../Types.hpp"

namespace Klang::Utilities {

template<class T>
class Memory {
public:
	static
	T *reallocate(Nat64 size, T *data, Nat64 space) {
		auto mlock = new T[space];
		for (Nat64 i = 0; i < size; ++i)
			mlock[i] = data[i];
		return mlock;
	}
};

}

#endif // KLANG_UTILITIES_MEMORY_HPP
