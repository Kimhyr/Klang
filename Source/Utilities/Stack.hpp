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
		: top_(nil), size_(0) {}

	~Stack() {
		for (Frame *frame; this->top_; this->top_ = frame) {
			frame = &this->top_->under;
			delete this->top_;
		}
	}

public:
	inline
	const T &top()
	const noexcept {return this->top_->value;}

	inline
	Nat64 size()
	const noexcept {return this->size_;}

public:
	inline
	Void push(T item) {
		this->top_ = new Frame(item, *this->top_);
		++size_;
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
	Frame *top_;
	Nat64 size_;
};

}

#endif // KLANG_UTILITIES_STACK_HPP
