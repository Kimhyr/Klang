#pragma once

#include <tuple>

#include "Types.h"

namespace Klang {

struct Token {
public:
	enum Category {
		NONE,
		
		PRIMITIVE,
		DETERMINER,

		LITERAL,

		UNARY_OPERATOR,
		BINARY_OPERATOR,
		SCOPED_TYPE,
	};
	
	enum Tag {
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
		QUOTE = '"',
	};
	
public:
	static constexpr nat16 const MAX_VALUE_LENGTH {1024};

public:
	Position start;
	Position end;
	Tag tag;
	union {
		char const* Name;
		nat64 Natural;
		real64 Real;
		char const* Text;
	} value;

public:
	void reset() {
		this->tag = Token::UNDEFINED;
		this->start.row = 0;
		this->start.column = 0;
		this->end.row = 0;
		this->end.column = 0;
		// switch (this->tag) {
		// 	// TODO: Test out if you can just delete `this->value.Name` because
		// 	// `this->value` is a union.
		// case Token_Tag::NAME: delete this->value.Name; break;
		// case Token_Tag::TEXT_LITERAL: delete this->value.Text; break;
		// default: break;
		// }
	}

public:
	:wcategory() {
		switch (this->tag) {
		case NATURAL:
		case FLOAT:
		case TEXT: return LITERAL;
		case PTR:
		case NAT:
		case NAT8:
		case NAT16:
		case NAT32:
		case NAT64:
		case INT:
		case INT8:
		case INT16:
		case INT32:
		case INT64:
		case REAL:
		case REAL32:
		case REAL64: return PRIMITIVE;
		case OBJECT: return DETERMINER;
		case SLOSH: return UNARY_OPERATOR;
		case COLON:
		case SEMICOLON:
		case EQUAL:
		case PLUS:
		case MINUS:
		case ASTERISKS:
		case SLASH:
		case PERCENT: return BINARY_OPERATOR;
		case OPAREN:
		case CPAREN: return SCOPED_TYPE;
		default: return NONE;
		}
	}
};

}

std::ostream& operator<<(std::ostream& os, Klang::Token const& token);

