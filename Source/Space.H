#ifndef KC_Space_H
#define KC_Space_H

#include "Definitions.H"

namespace KC {

struct Position {
	Nat64 row;
	Nat64 column;
};

struct Span {
	Position start;
	Position end;
};

struct Location {
	const Sym *path;
	Span span;
};

}

#endif // KC_Space_H
