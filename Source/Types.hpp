#pragma once
#ifndef KLANG_TYPES_HPP
#define KLANG_TYPES_HPP

namespace Klang {

#define nil nullptr
#define neg = -1

using Size = unsigned long int;

using Void = void;

using Bool = bool;
using Bool8 = unsigned char;
using Bool16 = unsigned short int;
using Bool32 = unsigned int;
using Bool64 = unsigned long int;

using Sym = char;

using Int = signed int;
using Int8 = signed char;
using Int16 = signed short int;
using Int32 = signed int;
using Int64 = signed long int;

using Nat = unsigned int;
using Nat8 = unsigned char;
using Nat16 = unsigned short int;
using Nat32 = unsigned int;
using Nat64 = unsigned long int;

using Real = double;
using Real32 = float;
using Real64 = double;

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

#endif // KLANG_TYPES_HPP
