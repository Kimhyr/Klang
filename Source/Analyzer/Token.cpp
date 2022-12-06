#ifndef KPLC_ANALYZER_TOKEN_CPP
#define KPLC_ANALYZER_TOKEN_CPP

#include "../Definitions.cpp"

struct TokenPoint {
    Nat64 Line;
    Nat64 Column;
};

enum class TokenSymbol : Nat16 {
    None = 0,
    End,
    Comment,

    // Punctuators
    OpenBrace = '{',
    CloseBrace = '}',
    OpenParen = '(',
    CloseParen = ')',
    OpenBracket = '[',
    CloseBracket = ']',
    Quote = '\"',
    Comma = ',',
    Semicolon = ';',

    // Operators
    Slosh = '\\',
    Lesser = '<',
    Greater = '>',
    Colon = ':',
    Equal = '=',
    Plus = '+',
    Minus = '-',
    Exclaim = '!',
    Question = '?',
    At = '@',
    And= '&',
    Line = '|',

    Identity = 256,
    Namespace,
    Enumerare,
    Structure,
    Unistruct,
    Implement,
    Procedure,
    Macro,
    Datum,
    Label,
    Alias,
    Match,
    Case,
    Loop,
    If,
    Elif,
    Else,
    Give,
    Stop,
    Drop,
    Roll,
    Yeet,

    Nat8,
    Nat16,
    Nat32,
    Nat64,
    Int8,
    Int16,
    Int32,
    Int64,

    Machine,
    Natural,
    Integer,
    Real,
    Text,

    // Punctuators
    DoubleColon, // ::

    // Operators
    Increment, // ++
    Decrement, // --
    RightArrow, // ->
    Equivalent, // ==
    LesserEquivalent, // <=
    GreaterEquivalent, // >=
    LeftShift, // <<
    RightShift, // >>
    DoubleAnd, // &&
    DoubleLine, // ||
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
