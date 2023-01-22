#pragma once
#ifndef KLANG_UTILITIES_STACK_HPP
#define KLANG_UTILITIES_STACK_HPP

#include "../Types.hpp"

namespace Klang::Utilities {

template<class T>
class Stack {
public:
	constexpr
	Stack()
		: _top(nil), _size(0) {}

	~Stack() {
		for (Frame *frame; this->_top; this->_top = frame) {
			frame = &this->_top->under;
			delete this->_top;
		}
	}

public:
	inline
	const T &top()
	const noexcept {return this->_top->value;}

	inline
	Nat64 size()
	const noexcept {return this->_size;}

public:
	inline
	Void push(T item) {
		this->_top = new Frame(item, *this->_top);
		++_size;
	}

	T pick();

	Void pop();

private:
	struct Frame {
	public:
		T value;
		Frame *under;
	
	public:
		constexpr
		Frame(T value, Frame *under)
			: value(value), under(under) {}
		
		constexpr
		~Frame() {this->value.~T();}
	};

private:
	Frame *_top;
	Nat64 _size;
};

}

#endif // KLANG_UTILITIES_STACK_HPP
