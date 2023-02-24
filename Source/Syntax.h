#pragma once

#include "Tokens.h"

#include <concepts>

namespace Klang {

namespace E {

struct E;

// Separator :=
//	E ('='|','|';'|...) E
struct Separator;

// Unary :=
//	E:Pre_Unary_Operation E:Term |
//	E:Term E:Post_Unary_Operation
struct Unary;

// Binary :=
//	E:Term T:Binary_Operation E:Term
struct Binary;

// Scoped :=
//	['{'|'('|'['] E:Term ['}'|')'|']'] 
struct Scoped;

// Literal :=
//	T:Literal
struct Literal;

// Object :=
// 	'object' O:Identifier ':' O:Type_Composition (';'|'=' E)
struct Object;

// struct Procedure;

// Type :=
// 	T:Primitive |
//	T:Determiner O:Identifier ?(':' O:Type_Composition) (';'|'{' E '}')
struct Type;

// Term :=
//	E:Unary | E:Binary | E:Scoped | E:Literal
struct Term;

}

namespace O {

struct O {};

enum class Determiner {
	OBJECT = static_cast<int>(Token_Tag::OBJECT),
};

// Identifier :=
//	('!'|'?') T:Name
// object!? value: Int 
struct Identifier: public O {
	Determiner determiner;
	std::string_view name;
	bool is_mutable = false;
	bool is_public = false;
	bool is_initialized = false;

public:
	bool operator==(Identifier const& other) const noexcept {
		if (this->determiner != other.determiner)
			return false;
		return other.name == this->name;
	}
};

struct Type_Composition: public O {
	natptr size;
	E::Type* root_type;
	Type_Composition* next;
};

}

namespace E {

enum Tag {
	NONE = 0,
	UNARY,
	BINARY,
	SCOPED,
	LITERAL,
	OBJECT = static_cast<int>(Token_Tag::OBJECT),
	TYPE,
};

struct E {
	Tag const tag = Tag::NONE;
	Position start;
	Position end;
	E* next;
	E* prior;

public:
	virtual ~E() = 0;
};

struct Term: public E {};

struct Unary: public Term {
	enum Operation: char {};
	
	Tag const tag = Tag::UNARY;
	Operation operation;
	Term* factor;
};

struct Binary: public Term {
	enum Operation: char {
		
	};
	
	Tag const tag = Tag::BINARY;
	Operation operation;
};

struct Scoped: public Term {
	enum Type {
		PAREN = static_cast<int>(Token_Tag::OPAREN),
	};
	
	Tag const tag = Tag::SCOPED;
	Term* first_term;
	Term* last_term;
};

struct Literal: public Term {
	enum Type {
		MACHINE = static_cast<int>(Token_Tag::MACHINE_LITERAL),
		NATURAL,
		INTEGER,
		REAL,
		TEXT,
	};

	Tag const tag = Tag::LITERAL;
	Type type;
	union {
		nat64 Machine;
		nat64 Natural;
		int64 Integer;
		real64 Real;
		char const* Text;
	} value;
};

struct Object: public E {
	Tag const tag = Tag::OBJECT;
	O::Identifier* identifier;
	O::Type_Composition type;
};

}

}
