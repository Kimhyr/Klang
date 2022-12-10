#ifndef KPLC_SYNTAX_IDENTIFIER_CPP
#define KPLC_SYNTAX_IDENTIFIER_CPP

#include "../Utilities/Flag.cpp"

namespace S {
    enum class IdentifierFlag {
        Mutable,
        Public,
    };

    struct Identifier {
<<<<<<< HEAD
        Flag8<IdentifierFlag> Flag;
=======
        Nat64 Depth; // I don't fucking know LOL
        U::Dynar<L::Identifier> Path;
>>>>>>> 766bc7e5c5445fb4cd2c73d68cc1d2105e7c4851
        const Text8 *Identity;
    };
} // S

#endif // KPLC_SYNTAX_IDENTIFIER_CPP
