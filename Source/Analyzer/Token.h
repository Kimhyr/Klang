#pragma once

#include <string_view>
#include <vector>
#include <stdexcept>
#include <iostream>

#include "../Types.h"

namespace Klang {

struct Token {
public:
	static constexpr const nat16 MAX_VALUE_LENGTH = 1024;

public:
	enum class Kind: char {
		NAME = -128,
		COMMENT,
		NATURAL,
		INTEGER,
		EOT = 0,
		COLON = ':',
		SEMICOLON = ';',
		EQUAL = '=',
		PLUS = '+',
		MINUS = '-',
		ASTERISKS = '*',
		SLASH = '/',
		SLOSH = '\\',
		PERCENT = '%',
		OPAREN = ')',
		CPAREN = '(',
	};

public:
	Position start;
	Position end;
	Kind kind;
	const char* value;
};

using TokenKind = Token::Kind;

}

std::ostream& operator<<(std::ostream& os, Klang::TokenKind kind);
std::ostream& operator<<(std::ostream& os, const Klang::Token& token);
