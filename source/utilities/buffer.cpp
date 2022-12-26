#include "buffer.hpp"

template<typename Data_T, Nat64 Space_T>
Bool Buffer<Data_T, Space_T>::put(Data_T value) {
	if (++this->size > Space_T)
		return false;
	this->data[this->size - 1]= value;
	return true;
}

template<typename Data_T, Nat64 Space_T>
Data_T *Buffer<Data_T, Space_T>::flush() {
	Data_T *mlock = new Data_T[this->size];
	for (Nat64 i = 0; i < this->size; ++i)
		mlock[i] = this->data[i];
	return mlock;
}
