// ['Int32'|'Nat8']

#ifndef KC_SYNTAX_PRIMITIVE_H
#define KC_SYNTAX_PRIMITIVE_H

#include "Syntax.H"

namespace S {
    struct Primitive {
        static constexpr
        const Syntax::Id Id = Syntax::PRIMITIVE;

    public:
        enum : Nat8 {
            INT32 = 3,
            NAT8,
        } Kind;
    };
} // S

#endif // KC_SYNTAX_PRIMITIVE_H
