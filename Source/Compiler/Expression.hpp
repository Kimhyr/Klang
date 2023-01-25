#pragma once
#ifndef KLANG_COMPILER_EXPRESSION_HPP
#define KLANG_COMPILER_EXPRESSION_HPP

#include "../Types.hpp"
#include "../Utilities/Table.hpp"

#include <string.h>

namespace Klang::Compiler {

class Parser;

enum class ExpressionTag {
	EXPRESSION,
	IDENTIFIER,
	PRIMITIVE,
	DATUM,
	FACTOR,
	BINARY,
};

struct Expression {
public:

	virtual ~Expression() = 0;

public:
	const Nat8 EPRE = 0;
	static constexpr const ExpressionTag ETAG = ExpressionTag::EXPRESSION;
};

namespace E {

using namespace Klang::Utilities;

struct Symbol: public Expression {};

struct Identifier: public Expression, public Hashable {
public:
	static constexpr const ExpressionTag ETAG = ExpressionTag::IDENTIFIER;

public:
	ExpressionTag tag;
	const Sym *name;

public:
	constexpr Bool operator ==(const Identifier &rhs) const noexcept {
		return this->tag == rhs.tag && strcmp(this->name, rhs.name) == 0;
	}

public:
	constexpr Size hash() override {
		Size result = 0;
		for (Nat16 i = 0; this->name[i]; ++i)
			result += this->name[i];
		return result;
	};
};

struct Type: public Symbol {};

// '-'? ['64'|'32'|'16'|'8'|'0'] '.'?
struct Primitive: public Type {
public:
	enum Type {
		INT32,
	};
	
public:
	static constexpr const ExpressionTag TAG = ExpressionTag::PRIMITIVE;

public:
	Type type;
};

// 'datum' Identifier ':' Type '=' E ';'
struct Datum: public Symbol {
public:
	static constexpr const ExpressionTag ETAG = ExpressionTag::DATUM;

public:
	const Identifier *identifier;
	const Type *type;
};

// [Literal|Datum] 
struct Factor: public Expression {
public:
	enum Kind {
		INTEGER,
		NATURAL,
		REAL,
		TEXT,
		DATUM,
	};

	union Value {
		Nat64 natural;
		Int64 integer;
		Real64 real;
		const Sym *text;
	};

public:
	static constexpr const ExpressionTag ETAG = ExpressionTag::FACTOR;

public:
	Kind kind;
	Value value;
};

// E ['='|'+'|'-'|'*'|'/'|'%'] E
struct Binary: public Expression {
public:
	enum Operation: Sym {
		STATEMENT,
		ASSIGN,
		ADD,
		SUBTRACT,
		MULTIPLY,
		DIVIDE,
		MOD,
	};

public:
	static constexpr const ExpressionTag ETAG = ExpressionTag::BINARY;

public:
	Operation operation;
	Expression *left;
	Expression *right;
};

}

}
#endif // KLANG_COMPILER_EXPRESSION_HPP
