#pragma once

#include "Syntax.h"

namespace Klang {

namespace S {

class Binary: public Syntax {
public:
	enum Operation {
		ADD = '+',
		SUBTRACT = '-',
		MULTIPLY = '*',
		DIVIDE = '/',
		MOD = '%',

		SEPARATE = ';',
	};

public:
	Tag const tag = BINARY;
	Operation operation;
	Syntax* first;
	Syntax* second;

public:
	constexpr Binary(Operation operation, Syntax* first) noexcept
		: operation(operation), first(first) {}
};

}

}
