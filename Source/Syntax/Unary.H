// ['return'] <Syntax>

#ifndef KC_SYNTAX_UNARY_H
#define KC_SYNTAX_UNARY_H

#include "Syntax.H"

namespace S {
    struct Unary {
        static constexpr
        const Syntax::Id Id = Syntax::UNARY;

    public:
        enum : Nat8 {
            RETURN,
        } Operand;
        Syntax Factor;
    };
} // S

#endif // KC_SYNTAX_UNARY_H
