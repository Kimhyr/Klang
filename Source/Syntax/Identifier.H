// <Identity>

#ifndef KC_SYNTAX_IDENTIFIER_H
#define KC_SYNTAX_IDENTIFIER_H

#include "Syntax.H"

namespace S {
    struct Identifier {
        static constexpr
        const Syntax::Id Id = Syntax::IDENTIFIER;

    public:
        const Sym8 *Identity;
    };
};

#endif // kKC_SYNTAX_IDENTIFIER_H
