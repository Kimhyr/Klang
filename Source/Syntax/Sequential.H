#ifndef KC_SYNTAX_SEQUENTIAL_H
#define KC_SYNTAX_SEQUENTIAL_H

#include "../Utilities/Dynar.H"
#include "Syntax.H"

namespace S {
    struct Sequential {
    public:
        using IDType = Nat8;

    public:
        enum : IDType {
            PARAMETER,
            BODY,
        };

    public:
        IDType ID;
        union {
            Dynar<Syntax> Body;
            Dynar<Datum> Parameters;
        } Value;
    };
} // S

#endif // KC_SYNTAX_SEQUENTIAL_H
