#ifndef KPLC_ANALYZER_TOKEN_CPP
#define KPLC_ANALYZER_TOKEN_CPP

#include "../Definitions.cpp"

struct TokenPoint {
    Nat64 Line;
    Nat64 Column;
};

enum class TokenEnum : Nat16 {
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
    TokenEnum Enum;
    TokenValue Value;

public:
    Void Destroy() {
        switch (this->Symbol) {
        case TokenEnum::Identity:
            delete[] this->Value.Identity;
            return;
        case TokenEnum::Text:
            delete[] this->Value.Text;
            return;
        default:
            return;
        }
    }
};

#endif // KPLC_ANALYZER_TOKEN_CPP
