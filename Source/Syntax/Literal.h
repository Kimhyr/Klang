#pragma once

#include "Syntax.h"

namespace Klang::S {

class Literal: public Syntax {
public:
	enum Tag: I8 {
		NATURAL = Syntax::NATURAL,
		REAL,
		STRING,
	};
	
	Syntax_Tag const tag;
	union Value {
		N Natural;
		R Real;
		String String {};
	} value;

public:
	constexpr Literal(Tag type, String&& value) noexcept
		: tag(static_cast<Syntax_Tag>(type)) {
		this->value.String = std::move(value);
	}

	constexpr Literal(Tag type, N natural) noexcept
		: tag(static_cast<Syntax_Tag>(type)) {
		this->value.Natural = natural;
	} 

	constexpr Literal(Tag type, R value) noexcept
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
