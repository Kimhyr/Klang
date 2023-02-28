#pragma once

#include <vector>

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
	bool is_used = false;
	bool is_mutable = false;
	bool is_defined = false;
	std::string_view name;
	Artifact* underlay;
};

struct Type_Composition {
public:
	bool is_mutable = false;
	std::vector<Artifact*> types;
	Type_Composition* next = nullptr;
};

struct Parameter {
public:
	natptr count = 0;
	Artifact* first = nullptr;
	Artifact* last;
};

struct Body {
public:
	natptr count = 0;
	Syntax* first = nullptr;
	Syntax* last;
};

}

}

#include "Unary.h"
#include "Binary.h"
#include "Scoped.h"
#include "Literal.h"
