#ifndef KC_Token_H
#define KC_Token_H

#include "Space.H"

namespace KC {

class Lexer;

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
	Token(Position start);

	~Token();

public:
	constexpr
	const Location *location()
	const noexcept { return &this->location_; }

	constexpr
	Tag tag()
	const noexcept { return this->tag_; }

	constexpr
	const Sym *value()
	const noexcept { return this->value_; }

private:
	Location location_;
	Tag tag_;
	Sym *value_;
};

}

#endif // KC_Token_H
