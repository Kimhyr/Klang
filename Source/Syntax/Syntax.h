#pragma once

#include "Lexeme.h"

namespace Klang {

class Syntax {
public:
	enum Tag: I8 {
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
		PARENTHESIS = Lexeme::O_PAREN,
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
