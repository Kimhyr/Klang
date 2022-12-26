#ifndef _BUFFER_HPP
#define _BUFFER_HPP

#include "../definitions.hpp"

template<typename Data_T, Nat64 Space_T>
class Buffer {
	Nat64 size;
	Data_T data[Space_T];

public:
	Buffer() = default;

	~Buffer() = default;

public:
	Bool put(Data_T value);

	Data_T *flush();
};

#endif // _BUFFER_HPP
