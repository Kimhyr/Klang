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
        const Text8 *Identity;
    };
} // S

#endif // KPLC_SYNTAX_IDENTIFIER_CPP
