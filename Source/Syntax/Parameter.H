// <Datum> (',' <Parameter>)? ')'

#ifndef KC_SYNTAX_PARAMETER_H
#define KC_SYNTAX_PARAMETER_H

#include "../Utilities/Dynar.H"
#include "Syntax.H"

namespace S {
    struct Parameter {
        static constexpr
        const Syntax::Id Id = Syntax::PARAMETER;

    public:
        Dynar<Datum> Parameters;
    };
} // S

#endif // KC_SYNTAX_PARAMETER_H
