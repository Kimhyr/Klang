#pragma once

#include "Token.h"

namespace Klang {

enum class ExpressionTag: char {
	IDENTIFIER,
	UNARY,
	BINARY,
	SCOPE,
	PRIMITIVE,
	LITERAL,
};

struct Expression {
public:
	const ExpressionTag tag;
	Position start;
	Position end;
};

template<ExpressionTag tag_T>
struct ExpressionBase
	: public Expression {
public:
	const ExpressionTag tag {tag_T};
};

struct Factor: public Expression {};
struct Type: public Expression {};

enum class IdentifierDeterminer: char {
	OBJECT = static_cast<char>(TokenTag::OBJECT),
};

struct Identifier
	: public ExpressionBase<ExpressionTag::IDENTIFIER> {
public:
	IdentifierDeterminer determiner;
	const char* name;
	Type& type;
};

enum class UnaryOperation: char {};

struct Unary
	: public ExpressionBase<ExpressionTag::UNARY>,
	  public Factor {
public:
	UnaryOperation operation;
	Factor* root;
};

enum class BinaryOperation: char {
	ADD = '+',
	SUBTRACT = '-',
	MULTIPLY = '*',
	DIVIDE = '/',
	MOD = '%',
	SEPARATE = ';',
};

struct Binary
	: public ExpressionBase<ExpressionTag::BINARY>,
	  public Factor {
public:
	BinaryOperation operation;
	Expression& first;
	Expression* second;
};

enum class ScopeType: char {
	CLOSED = '(',
};

struct Scope
	: public ExpressionBase<ExpressionTag::SCOPE>,
	  public Factor {
public:
	ScopeType type;
	Expression* root;
	Expression* head;
};

enum class PrimitiveType: char {
	PTR = static_cast<char>(TokenTag::PTR),
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
};

struct Primitive
	: public ExpressionBase<ExpressionTag::PRIMITIVE>,
	  public Type {
public:
	
	const PrimitiveType type;
};

constexpr const Primitive PtrPrimitive { .type = PrimitiveType::PTR };
constexpr const Primitive NatPrimitive { .type = PrimitiveType::NAT };
constexpr const Primitive Nat8Primitive { .type = PrimitiveType::NAT8 };
constexpr const Primitive Nat16Primitive { .type = PrimitiveType::NAT16 };
constexpr const Primitive Nat32Primitive { .type = PrimitiveType::NAT32 };
constexpr const Primitive Nat64Primitive { .type = PrimitiveType::NAT64 };
constexpr const Primitive IntPrimitive { .type = PrimitiveType::INT };
constexpr const Primitive Int8Primitive { .type = PrimitiveType::INT8 };
constexpr const Primitive Int16Primitive { .type = PrimitiveType::INT16 };
constexpr const Primitive Int32Primitive { .type = PrimitiveType::INT32 };
constexpr const Primitive Int64Primitive { .type = PrimitiveType::INT64 };
constexpr const Primitive RealPrimitive { .type = PrimitiveType::REAL };
constexpr const Primitive Real32Primitive { .type = PrimitiveType::REAL32 };
constexpr const Primitive Real64Primitive { .type = PrimitiveType::REAL64 };

}
