// <Syntax>* '}'

#ifndef KC_SYNTAX_BODY_H
#define KC_SYNTAX_BODY_H

#include "../Utilities/Dynar.H"
#include "Syntax.H"

namespace S {
    struct Body {
        static constexpr
        const Syntax::Id Id = Syntax::BODY;

    public:
        Dynar<Syntax> Instructions;
    };
} // S

#endif // eC_SYNTAX_BODY_H
