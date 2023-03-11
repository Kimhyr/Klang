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
		PLUS = '+',
		MINUS = '-',
		ASTERISK = '*',
		SLASH = '/',
		PERCENT = '%',
		EQUAL = '=',
		O_PAREN = '(',
		C_PAREN = ')',
	};

public:
	static constexpr ::Klang::N16 MAX_VALUE_LENGTH {1024};
	
struct String {
	static constexpr C const* LITERAL_OBJECT = "object";

	static constexpr C const* UNDEFINED = "UNDEFINED";
	static constexpr C const* NAME = "NAME";
	static constexpr C const* NATURAL = "NATURAL";
	static constexpr C const* REAL = "REAL";
	static constexpr C const* STRING = "STRING";
	static constexpr C const* P = "P";
	static constexpr C const* N = "N";
	static constexpr C const* N64 = "N64";
	static constexpr C const* N32 = "N32";
	static constexpr C const* N16 = "N16";
	static constexpr C const* N8 = "N8";
	static constexpr C const* I = "I";
	static constexpr C const* I64 = "I64";
	static constexpr C const* I32 = "I32";
	static constexpr C const* I16 = "I16";
	static constexpr C const* I8 = "I8";
	static constexpr C const* R = "R";
	static constexpr C const* R64 = "R64";
	static constexpr C const* R32 = "R32";
	static constexpr C const* OBJECT = "OBJECT";
	static constexpr C const* EOT = "EOT";
	static constexpr C const* DOT = "DOT";
	static constexpr C const* SLOSH = "SLOSH";
	static constexpr C const* COLON = "COLON";
	static constexpr C const* SEMICOLON = "SEMICOLON";
	static constexpr C const* EQUAL = "EQUAL";
	static constexpr C const* PLUS = "PLUS";
	static constexpr C const* MINUS = "MINUS";
	static constexpr C const* ASTERISK = "ASTERISK";
	static constexpr C const* SLASH = "SLASH";
	static constexpr C const* PERCENT = "PERCENT";
	static constexpr C const* O_PAREN = "O_PAREN";
	static constexpr C const* C_PAREN = "C_PAREN";
};

public:
	Position start;
	Position end;
	Tag tag;
	union {
		C Undefined;
		::Klang::N64 Natural;
		::Klang::R64 Real;
		Klang::String String {}; // Also Name
	} value;
};

using Lexeme_Tag = Lexeme::Tag;

C const* to_string(Lexeme_Tag tag);

}

std::ostream& operator<<(std::ostream& os, Klang::Lexeme const& lexeme);
