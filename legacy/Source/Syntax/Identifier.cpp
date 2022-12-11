#ifndef KPLC_SYNTAX_IDENTIFIER_CPP
#define KPLC_SYNTAX_IDENTIFIER_CPP

#include "../Utilities/Flag.cpp"

namespace S {
    enum class IdentifierFlag {
        Mutable,
        Public,
    };

    struct Identifier {
        Flag8<IdentifierFlag> Flag;
        Nat64 Depth; // I don't fucking know LOL
        U::Dynar<L::Identifier> Path;
        const Text8 *Identity;
    };
} // S

#endif // KPLC_SYNTAX_IDENTIFIER_CPP
