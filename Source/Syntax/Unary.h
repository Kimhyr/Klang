#pragma once

#include "Syntax.h"

namespace Klang {

namespace S {

class Unary: public Syntax {
public:
	enum Operation {
		UNSIGN = '+',
		SIGN = '-',
	};

public:
	Tag const tag = UNARY;
	Syntax* prior;
	Syntax* next;
	Operation operation;
	Syntax* term;

public:
	constexpr Unary(Operation operation, Syntax* prior = nullptr, Syntax* term = nullptr) noexcept
		: prior(prior), next(nullptr), operation(operation), term(term) {}
};

}

}
