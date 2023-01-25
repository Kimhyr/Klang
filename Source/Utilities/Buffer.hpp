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
		: size_(0) {}

	~Buffer() = default;

public:
	inline constexpr
	const Sym *data()
	const noexcept {return this->data_;}

	inline constexpr
	Nat64 size()
	const noexcept {return this->size_;}

public:
	Void push(Sym datum) {
		if (++this->size_ >= Size_T)
			throw Error::OVERFLOW;
		this->data_[this->size_ - 1] = datum;
	}

	inline
	Sym *flush() {
		return Memory<Sym>::reallocate(this->size_, this->data_, this->size_);
	}
private:
	Sym data_[Size_T];
	Nat64 size_;
};

}

#endif // KLANG_UTILITIES_BUFFER_HPP
