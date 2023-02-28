#pragma once

#include "Syntax.h"

namespace Klang {

namespace S {

class Scoped: public Syntax {
public:
	enum Priority {
		HIGH = '{',
		MIDDLE = '(',
		LOW = '[',
	};

public:
	Tag const tag = SCOPED;
	Syntax* prior;
	Syntax* next;
	Priority priority;
	Body root;

public:
	constexpr Scoped(Priority priority, Syntax* prior = nullptr) noexcept
		: prior(prior), next(nullptr), priority(priority) {}
};

}

}
