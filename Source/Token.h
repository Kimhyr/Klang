#pragma once

#include <string_view>
#include <vector>
#include <stdexcept>

#include "Types.h"

namespace Klang {

struct Token {
public:
	static constexpr const nat16 MAX_VALUE_LENGTH = 1024;

public:
	enum class Kind: char {
		IDENTIFIER = -128,
		EOT = 0,
		COLON = ':',
		SEMICOLON = ';',
		EQUAL = '=',
		PLUS = '+',
		MINUS = '-',
		ASTERISKS = '*',
		SLASH = '/',
		PERCENT = '%',
		OPAREN = ')',
		CPAREN = '(',
	};

public:
	Position start;
	Position end;
	std::string_view view;
	Kind kind;
	// Using a string_view rather than a union of varying types because you would
	// only convert to other types to simplify numeric expressions. I am not
	// implementing optimization features for now, and, even if I am, I would not
	// convert strings to numerics except during parsing.
	std::string_view value;
};

using TokenKind = Token::Kind;

}
