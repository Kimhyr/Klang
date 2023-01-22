#pragma once
#ifndef KLANG_UTILITIES_BUFFER_HPP
#define KLANG_UTILITIES_BUFFER_HPP

#include "Error.hpp"
#include "Memory.hpp"

namespace Klang::Utilities {

template<class T, Nat64 Size_T>
class Buffer {
public:
	constexpr
	Buffer()
		: _size(0) {}

	~Buffer() = default;

public:
	inline constexpr
	const Sym *data()
	const noexcept {return this->_data;}

	inline constexpr
	Nat64 size()
	const noexcept {return this->_size;}

public:
	Void push(Sym datum) {
		if (++this->_size >= Size_T)
			throw Error::OVERFLOW;
		this->_data[this->_size - 1] = datum;
	}

	inline
	Sym *flush() {
		return Memory<Sym>::reallocate(this->_size, this->_data, this->_size);
	}
private:
	Sym _data[Size_T];
	Nat64 _size;
};

}

#endif // KLANG_UTILITIES_BUFFER_HPP
