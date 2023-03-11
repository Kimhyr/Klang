#pragma once

#include "Syntax.h"

namespace Klang::S {

class Unary: public Syntax {
public:
	enum Tag: I8 {
		POSITIVE = Syntax::POSITIVE,
		NEGATIVE,
	};

public:
	Syntax_Tag const tag;
	Syntax* child;

public:
	constexpr Unary(Unary::Tag tag) noexcept
		: tag(static_cast<Syntax_Tag>(tag)) {}
};

using Unary_Tag = Unary::Tag;

};
