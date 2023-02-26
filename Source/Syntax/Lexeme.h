#pragma once

#include "../Types.h"

namespace Klang {

struct Lexeme {
public:
	enum Tag {
		UNDEFINED = -128,
		NAME,

	// Literals
		BINARY,
		FLOAT,
		STRING,

	// Primitives
		P = 'P' + 3,
		N = 'N', N64, N32, N16, N8,
		I = 'I', I64, I32, I16, I8,
		R = 'R' + 2, R64, R32,

	// Keywords
		OBJECT,

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
		OPAREN = '(',
		CPAREN = ')',
	};

public:
	static constexpr nat16 const MAX_VALUE_LENGTH {1024};
	
	static constexpr char const* OBJECT_KEYWORD = "object";
	static constexpr char const* INT_KEYWORD = "Int";

public:
	Position start;
	Position end;
	Tag tag;
	union {
		char Undefined;
		char* Name;
		nat64 Natural;
		real64 Float;
		char* String;
	} value;
};

}

std::ostream& operator<<(std::ostream& os, Klang::Lexeme const& token);
