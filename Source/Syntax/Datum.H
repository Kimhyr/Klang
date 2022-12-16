// 'datum' <Identifier> ('::' <Cast>)? [';'|'{' <Initializer>]

#ifndef KC_SYNTAX_DATUM_H
#define KC_SYNTAX_DATUM_H

#include "Syntax.H"
#include "Identifier.H"

namespace S {
    struct Initializer {
        static constexpr
        const Syntax::Id Id = Syntax::INITIALIZER;

    public:
        Identifier Identifier;
        NULLABLE(Type) Type;
        NULLABLE(Initializer) Initializer;
    };
} // S

#endif // KC_SYNTAX_DATUM_H
