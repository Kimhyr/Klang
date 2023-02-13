#pragma once

#include <map>

#include "Token.h"

namespace Klang {

enum class SyntaxTag: char {
	UNDEFINED,
	TREE,
	TYPE_COMPOSITION,
	IDENTIFIER,
	UNARY,
	BINARY,
	SCOPE,
	PRIMITIVE,
	LITERAL,
};

struct Syntax {
public:
	const SyntaxTag tag = SyntaxTag::UNDEFINED;
	Position start;
	Position end;

public:
	virtual ~Syntax() = default;
};

template<SyntaxTag tag_T>
struct SyntaxBase
	: public Syntax {
public:
	const SyntaxTag tag {tag_T};
};

struct Factor {};
struct Type {};

struct TypeComposition
	: public SyntaxBase<SyntaxTag::TYPE_COMPOSITION> {
public:
	Type* root;
	Type* head;
};


enum class IdentifierDeterminer: char {
	OBJECT = static_cast<char>(TokenTag::OBJECT),
};

enum class IdentifierFlag: bool8 {
	CLEAR = 0,
	INITIALIZED = 1,
	MUTABLE = 2,
};

struct IdentifierSignature {
public:
	IdentifierDeterminer determiner;
	const char* name;
};

struct Identifier
	: public SyntaxBase<SyntaxTag::IDENTIFIER> {
public:
	Syntax* mother;
	IdentifierSignature signature;
	TypeComposition type;
	IdentifierFlag flags;
	Syntax* next;
};

enum class LiteralType {
	NATURAL,
	INTEGER,
	REAL,
	SYMBOL,
	TEXT,
};

struct Literal
	: public SyntaxBase<SyntaxTag::LITERAL>,
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
	: public SyntaxBase<SyntaxTag::UNARY>,
	  public Factor {
public:
	UnaryOperation operation;
	Syntax* root;
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
	: public SyntaxBase<SyntaxTag::BINARY>,
	  public Factor {
public:
	BinaryOperation operation;
	Syntax* first;
	Syntax* second;
};

enum class ScopeType: char {
	CLOSED = '(',
};

struct Scope
	: public SyntaxBase<SyntaxTag::SCOPE>,
	  public Factor {
public:
	ScopeType type;
	Syntax* root;
	Syntax* head;
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
	: public SyntaxBase<SyntaxTag::PRIMITIVE>,
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

template<typename> struct IsOperation { static constexpr const bool value = true; };
template<> struct IsOperation<UnaryOperation> {};
template<> struct IsOperation<BinaryOperation> {};

template<typename T>
	requires IsOperation<T>::value
nat8 getPrecedence(T operation) {
	return operation;
}


struct SyntaxTree
	: public SyntaxBase<SyntaxTag::TREE> {
public:
	Syntax* root;
	Syntax* head;
	std::map<Identifier, Syntax*> symbols;

public:
	SyntaxTree() noexcept
		: root(nullptr), head(nullptr) {}
};

}

namespace std {

template<>
struct hash<Klang::Identifier> {
	size_t operator()(const Klang::Identifier& id) {
		return  (hash<const char*>()(id.name) << 2) +
			(static_cast<size_t>(id.determiner) >> (sizeof(size_t) * 8 - 2));
	}
};

}
