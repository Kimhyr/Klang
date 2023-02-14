#pragma once

#include "Tokens.h"

namespace Klang {

struct Literal_Expression;
enum class Literal_Type {
	NATURAL = static_cast<int>(Token_Tag::NATURAL),
};

struct Unary_Expression;
enum class Unary_Operation {
};

struct Binary_Expression;
enum class Binary_Operation {
	ASSIGN = '=',
	ADD = '+',
	SUBTRACT = '-',
	MULTIPLY = '*',
	DIVIDE = '/',
	MOD = '%',
};

struct Ternary_Expression;
enum class Ternary_Operation {
};

struct Scoped_Expression;
enum class Scope_Type {
	CLOSED = '(',
};

struct Simple_Expression;
enum class Simple_Operation {
};

struct Seperation;
enum class Separator {
	SEMICOLON = ';',
};

struct Primitive;
enum class Primitive_Type {
	PTR = static_cast<int>(Token_Tag::PTR),
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

struct Type_Composition;

struct Object_Declaration;
enum class Object_Flag {
	CLEAR = 0,
};

struct Factor {};
template<typename>
	struct Is_Factor { static constexpr const bool value = true; };
template<> struct Is_Factor<Unary_Expression> {};
template<> struct Is_Factor<Binary_Expression> {};
template<> struct Is_Factor<Ternary_Expression> {};
template<> struct Is_Factor<Scoped_Expression> {};

struct Type {};
template<typename>
	struct Is_Type { static constexpr const bool value = true; };
template<> struct Is_Type<Primitive> {};

enum class Symbol_Determiner {
	UNDEFINED = 0,
	LOW, // Procedures, constants, and objects.
	MEDIUM, // Structs, and enums.
	HIGH, // Modules.
};

struct Symbol {
public:
	const Symbol_Determiner determiner = Symbol_Determiner::UNDEFINED;
};

template<typename>
	struct Is_Symbol { static constexpr const bool value = true; };
template<typename T> requires Is_Type<T>::value struct Is_Symbol<T> {};
template<> struct Is_Symbol<Object_Declaration> {};

}
