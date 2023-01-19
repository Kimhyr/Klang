#ifndef KC_ANALYZER_EXPRESSION_H
#define KC_ANALYZER_EXPRESSION_H

#include "../definitions.h"

namespace KC::Analyzer {

struct Expression;

struct Binary {
	const enum class Tag : Sym {
		PLUS = '+',
		MINUS = '-',
		MULTIPLY = '*',
		DIVIDE = '/',
		MOD = '%',
		ASSIGN = '=',
		CAST = ':',
		STATEMENT = ';',
	} tag;
	Expression *first;
	Expression *second;
};

struct Scope {
	const enum class Tag : Sym {
		PAREN = '(',
	} tag;
	Expression *expression;
};

struct Expression {
	const enum class Tag : Nat8 {
		UNARY,
		BINARY,
		SCOPE,
	} tag;
	union {
		Binary binary;
		Scope scope;
	} value;

	Expression();
	~Expression() = default;
};

}

#endif // KC_ANALYZER_EXPRESSION_H
