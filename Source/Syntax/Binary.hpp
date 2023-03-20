#pragma once

#include "Syntax/Syntax.hpp"

namespace Klang::S {

class Binary: public Syntax {
public:
	enum Tag: std::int8_t {
		ADDITION = Syntax::ADDITION,
		SUBTRACTION = Syntax::SUBTRACTION,
		MULTIPLICATION = Syntax::MULTIPLICATION,
		DIVISION = Syntax::DIVISION,
		MODULUS = Syntax::MODULUS,
	};

public:
	Syntax_Tag const tag;

public:
	constexpr Binary(Tag tag) noexcept
		: tag(static_cast<Syntax_Tag>(tag)) {}
};

using Binary_Tag = Binary::Tag;

}
