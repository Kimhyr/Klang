#pragma once

#include <map>

#include "../Types.h"

namespace Klang {

struct Expression {
	const char* file;
	Position start;
	Position end;
};

enum class IdentifierKind {
	VALUE,
};

struct Identifier
	: public Expression {
public:
	const char* name;
	IdentifierKind kind;
};

enum class BinaryOperation {
	SEPARATE = ';',
	INFERENCE = ':',
	ASSIGN = '=',
	ADD = '+',
	SUBTRACT = '-',
	MULTIPLY = '*',
	DIVIDE = '/',
	MOD = '%',
};

struct Binary
	: public Expression {
public:
	BinaryOperation operation;
	Expression* first;
	Expression* second;
};

enum class ScopeKind {
	CLOSED = '(',
};

struct Scope
	: public Expression {
public:
	ScopeKind kind;
	Expression* root;
};

struct Value
	: public Expression {
public:
};

struct Program
	: public Expression {
public:
	std::map<Identifier, Expression*> symbols;
	Expression* root; 
};

};

namespace std {

template<>
struct hash<Klang::Identifier> {
	size_t operator()(const Klang::Identifier& key) {
		return (static_cast<size_t>(key.kind) << 62) +
		       (hash<const char*>()(key.name) >> 2);
	}
};

}
