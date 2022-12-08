// <L:Identifier> <- <T:Identity> [<T:Exclaim>|<T:Question>]?

#ifndef KPLC_SYNTAX_LEXEMES_IDENTIFIER_CPP
#define KPLC_SYNTAX_LEXEMES_IDENTIFIER_CPP

#include "../Utilities/Dynar.cpp"

namespace L {
    enum class IdentifierFlag {
        Mutable,
        PublicMutable,
    };

    struct Identifier {
        Nat64 Depth; // I don't fucking know LOL
        U::Dynar<Identifier> Path;
        const Text8 *Identity;
        IdentifierFlag Flag;
    };
} // L


#endif // KPLC_SYNTAX_LEXEMES_IDENTIFIER_CPP
