#include "dynamic.h"

namespace KC::Utilities {

template<typename Type_T>
Dynamic<Type_T>::Dynamic(Nat64 space)
	: data(new Type_T[space]), back(data), space(space) {
}

template<typename Type_T>
Dynamic<Type_T>::~Dynamic() {
	delete this->data;
}

template<typename Type_T>
Void Dynamic<Type_T>::put(Type_T datum) {
	if (this->getSize() + 1 > this->space)
		this->expand;
	this->back[-1] = datum;
}

template<typename Type_T>
Void Dynamic<Type_T>::pop() {
	if (this->data == this->back)
		return;
	--this->back;
}

template<typename Type_T>
Bool Dynamic<Type_T>::exists(Type_T query) const {
	for (Type_T *it = this->data; it != this->dataBack; ++it)
		if (*it == query)
			return true;
	return false;
}

template<typename Type_T>
template<typename ...Args_T>
Nat64 Dynamic<Type_T>::search(Bool (*query)(const Type_T *, Args_T...), Args_T... args) const {
	Nat64 size = this->getSize();
	for (Nat64 i = 0; i != size; ++i)
		if (query(&this->data[i], args...))
			return i;
	return -1;
}


}
