#ifndef KC_UTILITIES_BUFFER_H
#define KC_UTILITIES_BUFFER_H

#include "../definitions.h"

namespace KC {

template<typename Data_T, Nat64 Space_T>
class Buffer {
	Nat64 size;
	Data_T data[Space_T];

public:
	Buffer()
		: size(0) {}

	~Buffer() = default;

public:
	Void put(Data_T value) {
		if (++this->size > Space_T)
			throw Result::FAILURE;
		this->data[this->size - 1]= value;
	}

	Data_T *flush() {
		Data_T *mlock = new Data_T[this->size];
		for (Nat64 i = 0; i < this->size; ++i)
			mlock[i] = this->data[i];
		return mlock;
	}

	constexpr const Data_T *getData() const noexcept {
		return this->data;
	}
};

}

#endif // KC_UTILITIES_BUFFER_H
