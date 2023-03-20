#pragma once

#include "Syntax/Syntax.hpp"

namespace Klang::S {

class Literal: public Syntax {
public:
	enum Tag: int8_t {
		NATURAL = Syntax::NATURAL,
		REAL,
		STRING,
	};

	Syntax_Tag const tag;
	union Value {
		std::uint64_t Natural;
		std::float64_t Real;
		String String {};
	} value;

public:
	constexpr Literal(Tag type, String&& value) noexcept
		: tag(static_cast<Syntax_Tag>(type)) {
		this->value.String = std::move(value);
	}

	constexpr Literal(Tag type, std::uint64_t natural) noexcept
		: tag(static_cast<Syntax_Tag>(type)) {
		this->value.Natural = natural;
	}

	constexpr Literal(Tag type, std::float64_t value) noexcept
		: tag(static_cast<Syntax_Tag>(type)) {
		this->value.Real = value;
	}

	~Literal() noexcept {
		if (this->tag == static_cast<Syntax_Tag>(STRING))
			delete[] this->value.String.string;
	}
};

using Literal_Tag = Literal::Tag;

}
