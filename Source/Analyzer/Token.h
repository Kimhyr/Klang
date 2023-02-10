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
		COMMENT = -128,
		NAME,
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

public:
	Token()
		: start(0, 0), end(0, 0), kind(Kind::EOT), value(nullptr) {}

	~Token() {
		switch (this->kind) {
		case Kind::NAME:
		case Kind::NATURAL:
		case Kind::INTEGER: delete[] this->value; 
		default: break;
		}
	}
};

using TokenKind = Token::Kind;

}

std::ostream& operator<<(std::ostream& os, Klang::TokenKind kind);
std::ostream& operator<<(std::ostream& os, const Klang::Token& token);
