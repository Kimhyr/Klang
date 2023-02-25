#pragma once

#include <string_view>

#include "../Tokens.h"
#include "Syntax.h"

namespace Klang {

namespace S {

struct Literal: public Syntax {
public:
	enum Type {
		NATURAL = static_cast<int>(Token_Tag::NATURAL_LITERAL),
		REAL,
		TEXT,
	};

public:
	Tag const tag = LITERAL;
	Syntax* prior;
	Type type;
	union {
		natptr Natural;
		real64 Real;
		std::string_view Text;
	} value;
	Syntax* next;
};

}

}
