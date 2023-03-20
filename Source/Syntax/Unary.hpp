#pragma once

#include "Syntax/Syntax.hpp"

namespace Klang::S {

class Unary: public Syntax {
public:
	enum Tag: std::int8_t {
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
