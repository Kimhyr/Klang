#pragma once

#include <vector>
#include <string_view>

#include "../Types.h"

namespace Klang {

class Syntax {
public:
	using This_Type = Syntax;
	
	enum Tag {
		NONE,
	
		UNARY,
		BINARY,
		SCOPED,
		LITERAL,

		ARTIFACT,
	};

public:
	Tag const tag = NONE;
	Position start;
	Position end;

public:
	virtual ~Syntax() = 0;
};

namespace S {

class Unary;
class Binary;
class Scoped;
class Literal;

class Artifact;

struct Identifier;
struct Type_Composition;
struct Parameter;
struct Body;

struct Identifier {
public:
	B is_used = false;
	B is_mutable = false;
	B is_defined = false;
	std::string_view name;
	Artifact* underlay;
};

struct Type_Composition {
public:
	B is_mutable = false;
	Artifact* type;
	Type_Composition* next = nullptr;
};

struct Parameter {
public:
	N count = 0;
	Artifact* first = nullptr;
	Artifact* last;
};

struct Body {
public:
	N count = 0;
	Syntax* first = nullptr;
	Syntax* last;
};

}

}

#include "Unary.h"
#include "Binary.h"
#include "Scoped.h"
#include "Literal.h"
