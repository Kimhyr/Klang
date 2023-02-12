#pragma once

#include "Token.h"

namespace Klang {

enum class ExpressionTag: char {
	UNDEFINED,
	IDENTIFIER,
	UNARY,
	BINARY,
	SCOPE,
	PRIMITIVE,
	LITERAL,
};

struct Expression {
public:
	const ExpressionTag tag = ExpressionTag::UNDEFINED;
	Position start;
	Position end;

public:
	virtual ~Expression() = default;
};

template<ExpressionTag tag_T>
struct ExpressionBase
	: public Expression {
public:
	const ExpressionTag tag {tag_T};
};

struct Factor {};
struct Type {};

enum class IdentifierDeterminer: char {
	OBJECT = static_cast<char>(TokenTag::OBJECT),
};

enum class IdentifierFlag: bool8 {
	CLEAR = 0,
	INITIALIZED = 1,
	MUTABLE = 2,
};

struct Identifier
	: public ExpressionBase<ExpressionTag::IDENTIFIER> {
public:
	IdentifierDeterminer determiner;
	const char* name;
	Type* type;
	IdentifierFlag flags {IdentifierFlag::CLEAR};
};

enum class LiteralType {
	NATURAL,
	INTEGER,
	REAL,
	SYMBOL,
	TEXT,
};

struct Literal
	: public ExpressionBase<ExpressionTag::LITERAL>,
	  public Factor {
public:
	LiteralType type;
	union {
		nat64 Natural;
		int64 Integer;
		real64 Real;
		char Symbol;
		const char* Text;
		// Object* Object;
	} value;
	natptr size;
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
	Expression* first;
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

public:
	constexpr  Primitive(PrimitiveType type)
		: type(type) {}
};

constexpr const Primitive PTR_PRIMITIVE(PrimitiveType::PTR);
constexpr const Primitive NAT_PRIMITIVE(PrimitiveType::NAT);
constexpr const Primitive NAT8_PRIMITIVE(PrimitiveType::NAT8);
constexpr const Primitive NAT16_PRIMITIVE(PrimitiveType::NAT16);
constexpr const Primitive NAT32_PRIMITIVE(PrimitiveType::NAT32);
constexpr const Primitive NAT64_PRIMITIVE(PrimitiveType::NAT64);
constexpr const Primitive INT_PRIMITIVE(PrimitiveType::INT);
constexpr const Primitive INT8_PRIMITIVE(PrimitiveType::INT8);
constexpr const Primitive INT16_PRIMITIVE(PrimitiveType::INT16);
constexpr const Primitive INT32_PRIMITIVE(PrimitiveType::INT32);
constexpr const Primitive INT64_PRIMITIVE(PrimitiveType::INT64);
constexpr const Primitive REAL_PRIMITIVE(PrimitiveType::REAL);
constexpr const Primitive REAL32_PRIMITIVE(PrimitiveType::REAL32);
constexpr const Primitive REAL64_PRIMITIVE(PrimitiveType::REAL64);

}
