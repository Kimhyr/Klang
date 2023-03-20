#pragma once

#include "Syntax/Syntax.hpp"

namespace Klang::S {

class Scoped: public Syntax {
public:
	enum Tag: std::int8_t {
		PARENTHESIS = Syntax_Tag::PARENTHESIS,
	};

public:
	Syntax_Tag const tag;
	Syntax* first;
	Syntax* last;

public:
	constexpr Scoped(Tag type) noexcept
		: tag(static_cast<Syntax_Tag>(type)) {}
};

using Scoped_Tag = Scoped::Tag;

}
