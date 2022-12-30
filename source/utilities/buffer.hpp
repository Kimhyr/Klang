#ifndef KC_BUFFER_HPP
#define KC_BUFFER_HPP

#include "../definitions.hpp"

namespace KC {

template<typename Data_T, Nat64 Space_T>
class Buffer {
	Nat64 size;
	Data_T data[Space_T];

public:
	Buffer() = default;

	~Buffer() = default;

public:
	Void put(Data_T value);

	Data_T *flush() noexcept;
};

}

#endif // KC_BUFFER_HPP
