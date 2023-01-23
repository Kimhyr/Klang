#pragma once
#ifndef KLANG_COMPILER_TOKEN_HPP
#define KLANG_COMPILER_TOKEN_HPP

#include "../Types.hpp"

namespace Klang::Compiler {

struct Token {
public:
	friend class Lexer;

public:
	enum class Tag: Sym {
		DATUM = -128,

		END = 0,

		IDENTIFIER,
		MACHINE,
		NATURAL,
		INTEGER,
		REAL,
		TEXT,

		OPEN_PAREN = '(',
		CLOSE_PAREN = ')',

		COLON = ':', 
		SEMICOLON = ';',

		SLOSH = '\\',

		EQUAL = '=',
		PLUS = '+',
		MINUS = '-',
		ASTERISKS = '*',
		SLASH = '/',
		PERCENT = '%',
	};

public:
	static constexpr
	Nat64 VALUE_SPACE = 1024;

public:
	inline Token() noexcept
		: _value(nil) {}

	inline Token(Position start) noexcept
		: _span({.start = start}), _value(nil) {}
	
	inline Token(Span span, Tag tag, const Sym *value = nil) noexcept
		: _span(span), _tag(tag), _value(value) {}

	~Token() = default;

public:
	inline const Span &span() const noexcept {return this->_span;}
	inline Tag tag() const noexcept {return this->_tag;}
	inline const Sym *value() const noexcept {return this->_value;}

private:
	Span _span;
	Tag _tag;
	const Sym *_value;
};

}

#endif // KLANG_COMPILER_TOKEN_HPP
