#ifndef KLANG_COMPILER_TOKEN_HPP
#define KLANG_COMPILER_TOKEN_HPP

#include "../Types.hpp"

namespace Klang::Compiler {

class Token {
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
	constexpr
	Token()
		: _value(nil) {}

	constexpr
	Token(Position position)
		: _span({.start = position}), _value(nil) {}

	constexpr
	~Token() {
		if (_value)
			delete this->_value;
	}

public:
	inline constexpr
	const Span &span()
	const noexcept {return this->_span;}

	inline constexpr
	Tag tag()
	const noexcept {return this->_tag;}

	inline constexpr
	const Sym *value()
	const noexcept {return this->_value;}

private:
	Span _span;
	Tag _tag;
	Sym *_value;
};

}

#endif // KLANG_COMPILER_TOKEN_HPP
