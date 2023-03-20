#pragma once

#include "Syntax/Lexeme.hpp"

namespace Klang {

class Syntax {
public:
	enum Tag: std::int8_t {
		_,

	// Literal
		NATURAL = Lexeme::NATURAL,
		REAL = Lexeme::REAL,
		STRING = Lexeme::STRING,

	// Unary
		POSITIVE = Lexeme::PLUS,
		NEGATIVE = Lexeme::MINUS,

	// Binary
		ADDITION,
		SUBTRACTION,
		MULTIPLICATION = Lexeme::ASTERISK,
		DIVISION = Lexeme::SLASH,
		MODULUS = Lexeme::PERCENT,

	// Scope
		PARENTHESIS = Lexeme::LPAREN,
	};

public:
	Tag const tag = _;
	Span span;
	Syntax* prior;
	Syntax* next;

public:
	virtual ~Syntax() = 0;
};

namespace S {

class Literal;
class Unary;
class Scoped;

}

using Syntax_Tag = Syntax::Tag;

}

#include "Literal.h"
#include "Unary.h"
#include "Binary.h"
#include "Scoped.h"
