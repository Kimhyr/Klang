// <Syntax> ['::'|'='|'+'] <Syntax>

#ifndef KC_SYNTAX_BINRY_H
#define KC_SYNTAX_BINRY_H

#include "Syntax.H"

namespace S {
    struct Binary {
        static constexpr
        const Syntax::Id Id = Syntax::BINARY;

    public:
        enum : Nat8 {
            ADD,
            ASSIGN,
            CAST,
            SUBTRACT,
        } Operand;
        Syntax First;
        Syntax Second;
    };
} // S

#endif // KC_SYNTAX_BINRY_H
