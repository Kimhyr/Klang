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
        using IDType = Sym8;

    public:
        enum : IDType {
            UNARY,
            BINARY,
            SEQUENTIAL,
            IDENTIFIER,
            PROCEDURE,
            DATUM,
        };

    public:
        IDType ID;
        union {
            Unary *Unary;
            Binary *Binary;
            Sequential *Sequential;
        } Value;
    };
} // S

#endif // KC_SYNTAX_INCLUDE_H
