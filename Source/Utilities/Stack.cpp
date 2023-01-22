#include "Stack.hpp"

#include "Error.hpp"

namespace Klang::Utilities {

template<class T>
T Stack<T>::pick() {
	Frame *top = this->_top;
	if (!top)
		throw Error::UNDERFLOW;
	this->_top = top->under;
	T value = top->value;
	delete top;
	--_size;
	return value;
}

template<class T>
Void Stack<T>::pop() {
	Frame *top = this->_top;
	if (!top)
		throw Error::UNDERFLOW,
	this->_top = top->under;
	delete top;
	--_size;
}

}
