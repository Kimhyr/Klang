#pragma once

#include "Syntax.h"

namespace Klang::S {

class Scoped: public Syntax {
public:
	enum Tag: I8 {
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
