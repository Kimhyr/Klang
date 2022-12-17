// <Datum>* '}'

#ifndef KC_SYNTAX_INITIALIZER_H
#define KC_SYNTAX_INITIALIZER_H

#include "../Utilities/Dynar.H"
#include "Syntax.H"

namespace S {
    struct Intializer {
        static constexpr
        const Syntax::Id Id = Syntax::INITIALIZER;

    public:
        Dynar<Datum> Properties;
    };
} // S

#endif // KC_SYNTAX_INITIALIZER_H
