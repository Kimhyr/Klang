#ifndef KLANG_UTILITIES_MEMORY_HPP
#define KLANG_UTILITIES_MEMORY_HPP

#include "../Types.hpp"

namespace Klang::Utilities {

template<class Data_T>
class Memory {
public:
	static
	Data_T *reallocate(Nat64 size, Data_T *data, Nat64 space) {
		auto mlock = new Data_T[space];
		for (Nat64 i = 0; i < size; ++i)
			mlock[i] = data[i];
		return mlock;
	}
};

}

#endif // KLANG_UTILITIES_MEMORY_HPP
