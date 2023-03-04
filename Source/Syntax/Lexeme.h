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
		DOT = '.',
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
	
struct String {
	static constexpr S const* LITERAL_OBJECT = "object";

	static constexpr S const* UNDEFINED = "UNDEFINED";
	static constexpr S const* NAME = "NAME";
	static constexpr S const* NATURAL = "NATURAL";
	static constexpr S const* REAL = "REAL";
	static constexpr S const* STRING = "STRING";
	static constexpr S const* P = "P";
	static constexpr S const* N = "N";
	static constexpr S const* N64 = "N64";
	static constexpr S const* N32 = "N32";
	static constexpr S const* N16 = "N16";
	static constexpr S const* N8 = "N8";
	static constexpr S const* I = "I";
	static constexpr S const* I64 = "I64";
	static constexpr S const* I32 = "I32";
	static constexpr S const* I16 = "I16";
	static constexpr S const* I8 = "I8";
	static constexpr S const* R = "R";
	static constexpr S const* R64 = "R64";
	static constexpr S const* R32 = "R32";
	static constexpr S const* OBJECT = "OBJECT";
	static constexpr S const* EOT = "EOT";
	static constexpr S const* SLOSH = "SLOSH";
	static constexpr S const* COLON = "COLON";
	static constexpr S const* SEMICOLON = "SEMICOLON";
	static constexpr S const* EQUAL = "EQUAL";
	static constexpr S const* PLUS = "PLUS";
	static constexpr S const* MINUS = "MINUS";
	static constexpr S const* ASTERISKS = "ASTERISKS";
	static constexpr S const* SLASH = "SLASH";
	static constexpr S const* PERCENT = "PERCENT";
	static constexpr S const* O_PAREN = "O_PAREN";
	static constexpr S const* C_PAREN = "C_PAREN";
};

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

public:
	static S const* tag_to_string(Tag tag);
	inline S const* tag_to_string() {
		return Lexeme::tag_to_string(this->tag);
	}
};

}

std::ostream& operator<<(std::ostream& os, Klang::Lexeme const& token);
