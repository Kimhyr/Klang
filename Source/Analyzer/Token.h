#pragma once

#include "../Types.h"

namespace Klang {

enum class TokenTag: char {
	UNDEFINED = -128,
	NAME,
	NATURAL,
	FLOAT,
	TEXT,
	PTR,
	NAT,
	NAT8,
	NAT16,
	NAT32,
	NAT64,
	INT,
	INT8,
	INT16,
	INT32,
	INT64,
	REAL,
	REAL32,
	REAL64,
	COMMENT,
	OBJECT,
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

struct Token {
public:
	static constexpr const nat16 MAX_VALUE_LENGTH {1024};

public:
	TokenTag tag;
	Position start;
	Position end;
	union {
		const char* Name;
		nat64 Natural;
		int64 Integer;
		real64 Real;
		char Symbol;
		const char* Text;
	} value;

public:
	void reset() {
		this->tag = TokenTag::UNDEFINED;
		this->start.row = 0;
		this->start.column = 0;
		this->end.row = 0;
		this->end.column = 0;
		switch (this->tag) {
			// TODO: Test out if you can just delete `this->value.Name` because
			// `this->value` is a union.
		case TokenTag::NAME: delete this->value.Name; break;
		case TokenTag::TEXT: delete this->value.Text; break;
		default: break;
		}
	}

public:
	constexpr bool isLiteral() const noexcept {
		return this->tag >= TokenTag::NATURAL &&
		       this->tag <= TokenTag::TEXT;
	}
	
	constexpr bool isPrimitive() const noexcept {
		return this->tag >= TokenTag::PTR &&
		       this->tag <= TokenTag::REAL64;
	}
	
	constexpr bool isDeterminer() const noexcept {
		switch (this->tag) {
		case TokenTag::OBJECT:
			return true;
		default: return false;
		}
	}

	constexpr bool isUnary() const noexcept {
		switch (this->tag) {
		case TokenTag::SLOSH:
			return true;
		default: return false;
		}
	}
	
	constexpr bool isBinary() const noexcept {
		switch (this->tag) {
		case TokenTag::COLON:
		case TokenTag::SEMICOLON:
		case TokenTag::EQUAL:
		case TokenTag::PLUS:
		case TokenTag::MINUS:
		case TokenTag::ASTERISKS:
		case TokenTag::SLASH:
		case TokenTag::PERCENT:
			return true;	
		default: return false;
		}
	}

	constexpr bool isScope() const noexcept {
		switch (this->tag) {
		case TokenTag::OPAREN:
		case TokenTag::CPAREN:
			return true;
		default: return false;
		}
	}
};

}

std::ostream& operator<<(std::ostream& os, const Klang::Token& token);

