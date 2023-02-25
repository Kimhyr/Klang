#pragma once

#include "Syntax.h"

namespace Klang {

namespace S {

struct Scoped: public Syntax {
public:
	enum Priority {
		HIGH = '{',
		MIDDLE = '(',
		LOW = '[',
	};

public:
	Tag const tag = SCOPED;
	Syntax* prior;
	Priority priority;
	Syntax* root;
	Syntax* next;
};

}

}
