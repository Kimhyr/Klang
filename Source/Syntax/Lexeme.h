#pragma once

#include "../Doctor.h"
#include "../Types.h"

namespace Klang {

struct Lexeme {
public:
	enum Tag: I8 {
		UNDEFINED = -127,
		NAME,

	// Literals
		NATURAL,
		REAL,
		STRING,

	// Keywords
		OBJECT,
	
	// Primitives
		P = 'P' + 3,
		N = 'N', N64, N32, N16, N8,
		I = 'I', I64, I32, I16, I8,
		R = 'R' + 2, R64, R32,

	// Symbols
		EOT = 0,
		SLOSH = '\\',
		COLON = ':',
		SEMICOLON = ';',
		EQUAL = '=',
		PLUS = '+',
		MINUS = '-',
		ASTERISKS = '*',
		SLASH = '/',
		PERCENT = '%',
		O_PAREN = '(',
		C_PAREN = ')',
	};

public:
	static constexpr ::Klang::N16 MAX_VALUE_LENGTH {1024};
	
	static constexpr S const* OBJECT_KEYWORD {"object"};

public:
	Position start;
	Position end;
	Tag tag;
	union {
		S Undefined;
		S* Name;
		::Klang::N64 Natural;
		::Klang::R64 Real;
		S* String;
	} value;
};

}

std::ostream& operator<<(std::ostream& os, Klang::Lexeme const& token);
