#pragma once
#ifndef KLANG_COMPILER_EXPRESSION_HPP
#define KLANG_COMPILER_EXPRESSION_HPP

#include "../Types.hpp"

namespace Klang::Compiler {

struct Expression {
public:
	enum class Tag: Nat8 {
		NONE,
		DATUM,
		PRIMITIVE,
		BINARY,
	};
	
public:
	static constexpr
	const Tag TAG = Tag::NONE;
};

namespace E {

struct Primitive: public Expression {
public:
	enum class Type: Nat8 {
		INT32,
	};

public:
	static constexpr
	const Tag TAG = Tag::PRIMITIVE;
	
public:
	Type type;
};

struct Datum: public Expression {
public:
	static constexpr
	const Tag TAG = Tag::DATUM;

public:
	const Sym *name;
	Primitive *type;
	Expression *above;
	Expression *under;
};

struct Binary: public Expression {
public:
	enum class Operation: Sym {
		ASSIGN = '=',
		ADD = '+',
		SUBTRACT = '-',
		MULTIPLY = '*',
		DIVIDE = '/',
		MOD = '%',
	};

public:
	static constexpr
	Tag TAG = Tag::BINARY;

public:
	Operation operation;
	Expression *first;
	Expression *second;
};

}

}

#endif // KLANG_COMPILER_EXPRESSION_HPP
