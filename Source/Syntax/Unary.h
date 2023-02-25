#pragma once

#include "Syntax.h"

namespace Klang {

namespace S {

struct Unary: public Syntax {
public:
	enum Operation {
		UNSIGN = '+',
		SIGN = '-',
	};

public:
	Tag const tag = UNARY;
	Syntax* prior;
	Operation operation;
	Syntax* term;
	Syntax* next;
};

}

}
