#ifndef KC_DEFINITIONS_HPP
#define KC_DEFINITIONS_HPP

using Void = void;

using Sym = char;

using Bool = bool;


using Int = int;
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

enum class Result: Bool {
        FAILURE,
        SUCCESS,
};

#endif // KC_DEFINITIONS_HPP
