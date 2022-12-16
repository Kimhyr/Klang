// 'procedure' <Identifier> ('(' <Parameter>)? ('->' <Cast>)? [';'|'{' <Body>]

#ifndef KC_SYNTAX_PROCEDURE_H
#define KC_SYNTAX_PROCEDURE_H

#include "Syntax.H"
#include "Identifier.H"

namespace S {
    struct Procedure {
        static constexpr
        const Syntax::Id Id = Syntax::PROCEDURE;

    public:
        Identifier identifier;
        NULLABLE(Parameter) Parameter;
        NULLABLE(Type) Type;
        NULLABLE(Body) Body;
    };
} // S

#endif // KC_SYNTAX_PROCEDURE_H
