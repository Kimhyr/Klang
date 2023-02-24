#pragma once

#include "Tokens.h"

#include <concepts>

namespace Klang {

namespace E {

struct This;

struct Program;

// Unary :=
//	E:Pre_Unary_Operation E:This |
//	E:This E:Post_Unary_Operation
struct Unary;

// Binary :=
//	E:This T:Binary_Operation E:This
struct Binary;

// Scoped :=
//	['{'|'('|'['] E:This ['}'|')'|']'] 
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

// This :=
//	E:Unary | E:Binary | E:Scoped | E:Literal

}

namespace O {

struct This {};

enum class Determiner {
	OBJECT = static_cast<int>(Token_Tag::OBJECT),
};

// Identifier :=
//	('!'|'?') T:Name
// object!? value: Int 
struct Identifier: public O::This {
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

struct Type_Composition: public O::This {
	E::Type* type;
	Type_Composition* next;
};

}

namespace E {

enum Tag {
	NONE = 0,
	PROGRAM,
	UNARY,
	BINARY,
	SCOPED,
	LITERAL,
	OBJECT = static_cast<int>(Token_Tag::OBJECT),
	TYPE,
};

struct This {
	Tag const tag = Tag::NONE;
	Position start;
	Position end;
	This* next;
	This* prior;

public:
	virtual ~This() = 0;

public:
	constexpr bool is_assignable() const noexcept {
		switch (this->tag) {
		case Tag::OBJECT: return true;
		default: return false;
		}
	};
};

struct Unary: public This {
	enum Operation: char {};
	
	Tag const tag = Tag::UNARY;
	Operation operation;
	This* factor;
};

struct Binary: public This {
	enum Operation: char {
		
	};
	
	Tag const tag = Tag::BINARY;
	Operation operation;
};

struct Scoped: public This {
	enum Type {
		PAREN = static_cast<int>(Token_Tag::OPAREN),
	};
	
	Tag const tag = Tag::SCOPED;
	This* first_term;
	This* last_term;
};

struct Literal: public This {
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

struct Object: public This {
	Tag const tag = Tag::OBJECT;
	O::Identifier identifier;
	O::Type_Composition type;
};

struct Program: public This {};

}

}
