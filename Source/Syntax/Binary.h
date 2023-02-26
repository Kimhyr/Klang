#pragma once

#include "Syntax.h"

namespace Klang {

namespace S {

struct Binary: public Syntax {
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
	Syntax* first;
	Operation operation;
	Syntax* second;
};

}

}
