#ifndef KC_INCLUDE_H
#define KC_INCLUDE_H

#include <stdio.h>
#include <stdlib.h>

#define $ this->

#define TRUE true
#define FALSE false
#define NIL nullptr
#define UNIMPLEMENTED(msg) \
        do { \
                printf("Unimplemented [%s:%i]: %s", \
                       __FILE__, __LINE__, msg); \
                exit(1); \
        } while (0)

using Void = void;

using Sym8 = char;
using Sym6 = wchar_t;

using Bool = bool;

using Bit8 = unsigned char;
using Bit16 = unsigned short int;
using Bit32 = unsigned int;
using Bit64 = unsigned long long int;

using Int8 = signed char;
using Int16 = signed short int;
using Int32 = signed int;
using Int64 = signed long long int;

using Nat8 = unsigned char;
using Nat16 = unsigned short int;
using Nat32 = unsigned int;
using Nat64 = unsigned long long int;

using Real32= float;
using Real64 = double;

using Size = unsigned long long int;

enum class Result : Int8 {
    FAILURE = -1,
    SUCCESS,
};

#endif // KC_INCLUDE_H
