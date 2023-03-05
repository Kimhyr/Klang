#pragma once

#include <string_view>

#include "Lexeme.h"
#include "Syntax.h"

namespace Klang {

namespace S {

class Literal: public Syntax {
public:
	enum Type {
		NATURAL = static_cast<int>(Lexeme::NATURAL),
		FLOAT,
		STRING,
	};

public:
	Tag const tag = LITERAL;
	Syntax* prior;
	Syntax* next;
	Type type;
	union Value {
		N Natural;
		R Real;
		char const* Text;
	} value;

public:
	constexpr Literal(Type type, Value value, Syntax* prior = nullptr) noexcept
		: prior(prior), type(type), value(value) {}
};

}

}
