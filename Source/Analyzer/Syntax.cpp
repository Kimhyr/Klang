#ifndef KPLC_SYNTAX_CPP
#define KPLC_SYNTAX_CPP

#include "../Symbol.cpp"
#include "../Utilities/Dynar.cpp"

struct Syntax {};

namespace S {
    enum class SimpleOperation {
        Give,
    };

    struct Simple : public Syntax {
        SimpleOperation Operation,
        Syntax *Value; // Nullable
    };

    enum class BinaryOperation {
        Add,
    };

    // <Syntax> <BinaryOperation> <Syntax> ';'
    struct Binary : public Syntax {
        BinaryOperation Operation;
        Syntax *First;
        Syntax Second;
    };

    // <Symbol> '=' <Syntax> ';'
    struct Assign : public Syntax {
        Symbol *Symbol;
        Syntax Value;
    };

    // <Syntax>* '}'
    struct Body : public Syntax {
        U::Dynar<Syntax> Organs;
    };

    // '@'* <Symbol>
    struct Cast : public Syntax {
        Nat8 Pointers;
        Symbol *Type;
    };

    // 'datum' <Symbol> ':' <Cast> '{' <Body>
    struct Datum : public Syntax {
        S::Cast Cast;
        S::Body Body;
    };

    // <Datum> (',' <Argument>)? ')'
    struct Argument : public Syntax {
        U::Dynar<S::Datum> Arguments;
    };

    // procedure <Symbol> ('(' <Argument>)? ('->' <Cast>)? [';'|'{' <Body>]
    struct Procedure : public Syntax {
        S::Argument Arguments;
        S::Cast Cast;
        S::Body Body;
    };
} // S

#endif // KPLC_SYNTAX_CPP
