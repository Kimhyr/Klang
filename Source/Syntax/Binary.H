#ifndef KC_SYNTAX_BINARY_H
#define KC_SYNTAX_BINARY_H

#include "Syntax.H"

namespace S {

    struct Binary {
    public:
        using IDType = Nat8;

    public:
        enum : IDType {
            PLUS,
            MINUS,
            EQUAL,
            CAST,
        };

    public:
        Syntax Second;
        Syntax *First;
        IDType Operand;
    };
} // S

#endif // KC_SYNTAX_BINARY_H