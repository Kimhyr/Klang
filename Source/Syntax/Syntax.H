#ifndef KC_SYNTAX_INCLUDE_H
#define KC_SYNTAX_INCLUDE_H

#include "../Include.H"

#define KIND(N) \
    NULLABLE(N) N

namespace S {
    struct Binary;
    struct Body;
    struct Datum;
    struct Identifier;
    struct Initializer;
    struct Parameter;
    struct Primitive;
    struct Procedure;
    struct Simple;
    struct Type;
    struct Unary;

    struct Syntax {
    public:
        using Id = Nat8;

    public:
        enum : Id {
            BINARY,
            BODY,
            DATUM,
            IDENTIFIER,
            INITIALIZER,
            PARAMETER,
            PRIMITIVE,
            PROCEDURE,
            TYPE,
            UNARY,
        } Kind;
        union {
            KIND(Binary);
            KIND(Body);
            KIND(Datum);
            KIND(Identifier);
            KIND(Initializer);
            KIND(Parameter);
            KIND(Primitive);
            KIND(Procedure);
            KIND(Syntax);
            KIND(Type);
            KIND(Unary);
        } Value;
    };
} // S

#endif // KC_SYNTAX_INCLUDE_H
