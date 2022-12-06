#ifndef KPLC_SYMBOL_CPP
#define KPLC_SYMBOL_CPP

#include "Analyzer/Syntax.cpp"

// Comparison is faster

enum class SymbolType {
    Procedure,
    Datum,
};

union SymbolValue {
    const S::Procedure *Procedure;
    const S::Datum *Datum;
};

struct Symbol {
    Nat64 Depth;
    const Text8 *Identity;
    SymbolType Type;
    SymbolValue Value;
};

#endif // KPLC_SYMBOL_CPP
