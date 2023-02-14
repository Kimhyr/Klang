#pragma once

#include "Types.h"

namespace Klang {

enum class Token_Tag {
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
	Token_Tag tag;
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
		this->tag = Token_Tag::UNDEFINED;
		this->start.row = 0;
		this->start.column = 0;
		this->end.row = 0;
		this->end.column = 0;
		switch (this->tag) {
			// TODO: Test out if you can just delete `this->value.Name` because
			// `this->value` is a union.
		case Token_Tag::NAME: delete this->value.Name; break;
		case Token_Tag::TEXT: delete this->value.Text; break;
		default: break;
		}
	}

public:
	constexpr bool is_literal() const noexcept {
		return this->tag >= Token_Tag::NATURAL &&
		       this->tag <= Token_Tag::TEXT;
	}
	
	constexpr bool is_primitive() const noexcept {
		return this->tag >= Token_Tag::PTR &&
		       this->tag <= Token_Tag::REAL64;
	}
	
	constexpr bool is_determiner() const noexcept {
		switch (this->tag) {
		case Token_Tag::OBJECT:
			return true;
		default: return false;
		}
	}

	constexpr bool is_unary() const noexcept {
		switch (this->tag) {
		case Token_Tag::SLOSH:
			return true;
		default: return false;
		}
	}
	
	constexpr bool is_binary() const noexcept {
		switch (this->tag) {
		case Token_Tag::COLON:
		case Token_Tag::SEMICOLON:
		case Token_Tag::EQUAL:
		case Token_Tag::PLUS:
		case Token_Tag::MINUS:
		case Token_Tag::ASTERISKS:
		case Token_Tag::SLASH:
		case Token_Tag::PERCENT:
			return true;	
		default: return false;
		}
	}

	constexpr bool is_scope() const noexcept {
		switch (this->tag) {
		case Token_Tag::OPAREN:
		case Token_Tag::CPAREN:
			return true;
		default: return false;
		}
	}
};

}

std::ostream& operator<<(std::ostream& os, const Klang::Token& token);

