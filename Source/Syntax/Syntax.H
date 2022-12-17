#ifndef KC_SYNTAX_INCLUDE_H
#define KC_SYNTAX_INCLUDE_H

#include "../Include.H"

namespace S {
    struct Unary;
    struct Binary;
    struct Sequential;
    struct Datum;

    struct Syntax {
    public:
        using Id = Sym8;

    public:
        enum : Id {
            UNARY,
            BINARY,
            SEQUENTIAL,
            IDENTIFIER,
            PROCEDURE,
            DATUM,
        };

    public:
        Id ID;
        union {
            Unary *Unary;
            Binary *Binary;
            Sequential *Sequential;
            Datum *Datum;
        } Value;
    };
} // S

#endif // KC_SYNTAX_INCLUDE_H
