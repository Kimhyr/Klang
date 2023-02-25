#pragma once

#include <vector>

#include "../Types.h"

namespace Klang {

struct Syntax {
public:
	using This_Type = Syntax;
	
	enum Tag {
		NONE,
	
		UNARY,
		BINARY,
		SCOPED,
		LITERAL,
		
		OBJECT,
		TYPE,
	};

public:
	Tag const tag = NONE;
	Position start;
	Position end;

public:
	virtual ~Syntax() = 0;
};

namespace S {

struct Unary;
struct Binary;
struct Scoped;
struct Literal;

struct Object;
struct Type;

struct Identifier;
struct Type_Composition;
struct Parameter;
struct Body;

struct Identifier {
public:
	enum Determiner {
		OBJECT = Syntax::OBJECT,
		PROCEDURE,
		TYPE,
	};
	
public:
	bool is_used = false;
	bool is_mutable = false;
	bool is_initiated = false;
	Determiner determiner;
	std::string_view name;
	union {
		Object* Object;
		Type* Type;
	} underlay;
};

struct Type_Composition {
public:
	bool is_mutable = false;
	std::vector<Type*> types;
	Type_Composition* next = nullptr;
};

struct Parameter {
public:
	natptr count = 0;
	Object* first = nullptr;
	Object* last;
};

struct Body {
public:
	natptr count = 0;
	Syntax* first = nullptr;
	Syntax* last;
};

}
}
