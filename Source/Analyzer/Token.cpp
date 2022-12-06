#ifndef KPLC_ANALYZER_TOKEN_CPP
#define KPLC_ANALYZER_TOKEN_CPP

#include "../Definitions.cpp"

struct TokenPoint {
    Nat64 Line;
    Nat64 Column;
};

enum class TokenSymbol : Nat16 {
#include "Defs/Token.defs"
};

union TokenValue {
    Text8 None;
    const Text8 *Identity;
    Nat64 Natural;
    Int64 Integer;
    Real64 Real;
    Bit64 Machine;
    const Text8 *Text;
};

struct Token {
    TokenPoint Start;
    TokenPoint End;
    TokenSymbol Symbol;
    TokenValue Value;

public:
    Void Destroy() {
        switch (this->Symbol) {
        case TokenSymbol::Identity:
            delete[] this->Value.Identity;
            return;
        case TokenSymbol::Text:
            delete[] this->Value.Text;
            return;
        default:
            return;
        }
    }
};

#endif // KPLC_ANALYZER_TOKEN_CPP
