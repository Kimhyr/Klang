// '@'* <Identifier>

#ifndef KC_SYNTAX_TYPE_H
#define KC_SYNTAX_TYPE_H

#include "Syntax.H"

namespace S {
    struct Type {
        static constexpr
        const Syntax::Id Id = Syntax::TYPE;

    public:
        Nat8 Pointers;
        union {
            NULLABLE(Primitive) Primitive;
        } Type;
    };
} // S

#endif // KC_SYNTAX_TYPE_H
