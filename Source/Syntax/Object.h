#pragma once

#include "Syntax.h"

namespace Klang {

namespace S {

/*

object lambda(): int = {
	return 0;
};

procedure proc(value: int, lambda(): int) {
	
}

*/

// Doubles as a procedure.
struct Object: public Syntax {
public:
	Tag const tag = OBJECT;
	Syntax* prior;
	Identifier identifier;
	Parameter parameter;
	Type_Composition type;
	Body body;
	Syntax* next;
};


}

}
