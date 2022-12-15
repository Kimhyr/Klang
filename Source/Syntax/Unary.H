#ifndef KC_SYNTAX_UNARY_H
#define KC_SYNTAX_UNARY_H

#include "Syntax.H"

namespace S {
    struct Unary {
    public:
        using IDType = Nat8;

    public:
        enum : IDType {
            RETURN,
        };

    public:
        IDType ID;
        Syntax Value;
    };
} // S

#endif // KC_SYNTAX_UNARY_H
