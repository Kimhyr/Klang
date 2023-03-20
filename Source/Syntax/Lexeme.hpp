#pragma once

#include "Doctor.hpp"
#include "Types.hpp"

namespace Klang {

struct Lexeme {
public:
	enum Tag: std::int8_t {
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
		LPAREN = '(',
		RPAREN = ')',
	};

public:
	static constexpr uint16_t MAX_VALUE_LENGTH {1024};

struct String {
	static constexpr char const* LITERAL_OBJECT = "object";

	static constexpr char const* UNDEFINED = "UNDEFINED";
	static constexpr char const* NAME = "NAME";
	static constexpr char const* NATURAL = "NATURAL";
	static constexpr char const* REAL = "REAL";
	static constexpr char const* STRING = "STRING";
	static constexpr char const* P = "P";
	static constexpr char const* N = "N";
	static constexpr char const* N64 = "N64";
	static constexpr char const* N32 = "N32";
	static constexpr char const* N16 = "N16";
	static constexpr char const* N8 = "N8";
	static constexpr char const* I = "I";
	static constexpr char const* I64 = "I64";
	static constexpr char const* I32 = "I32";
	static constexpr char const* I16 = "I16";
	static constexpr char const* I8 = "I8";
	static constexpr char const* R = "R";
	static constexpr char const* R64 = "R64";
	static constexpr char const* R32 = "R32";
	static constexpr char const* OBJECT = "OBJECT";
	static constexpr char const* EOT = "EOT";
	static constexpr char const* DOT = "DOT";
	static constexpr char const* SLOSH = "SLOSH";
	static constexpr char const* COLON = "COLON";
	static constexpr char const* SEMICOLON = "SEMICOLON";
	static constexpr char const* EQUAL = "EQUAL";
	static constexpr char const* PLUS = "PLUS";
	static constexpr char const* MINUS = "MINUS";
	static constexpr char const* ASTERISK = "ASTERISK";
	static constexpr char const* SLASH = "SLASH";
	static constexpr char const* PERCENT = "PERCENT";
	static constexpr char const* LPAREN = "LPAREN";
	static constexpr char const* RPAREN = "RPAREN";
};

public:
	Position start;
	Position end;
	Tag tag;
	union {
		char Undefined;
		std::uint64_t Natural;
		std::float64_t Real;
		Klang::String String {}; // Also Name
	} value;
};

using Lexeme_Tag = Lexeme::Tag;

char const* to_string(Lexeme_Tag tag);

}

std::ostream& operator<<(std::ostream& os, Klang::Lexeme const& lexeme);
