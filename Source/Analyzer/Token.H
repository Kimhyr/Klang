#ifndef KC_ANALYZER_TOKEN_H
#define KC_ANALYZER_TOKEN_H

#include "../Include.H"
#include "../Location.H"

enum class TokenID {
    // Exotic
    NONE = 0,
    END,
    COMMENT,

    // Keywords
    INT32,
    NAT8,

    // Literals
    MACHINE,
    NATURAL,
    INTEGER,
    REAL,
    TEXT,

    // Symbols
    OPEN_PAREN = '(',
    CLOSE_PAREN = ')',
    OPEN_BRACE = '{',
    CLOSE_BRACE = '}',

    COMMA = ',',
    SEMICOLON = ';',

    SLOSH = '\\',

    AT = '@',
    QUESTION = '?',

    EQUAL = '=',
    PLUS = '+',
    MINUS = '-',

    // Exotic
    IDENTIFIER = -128,

    // Keywords
    PROCEDURE,
    DATUM,
    RETURN,

    // Symbols
    DOUBLE_COLON, // ::
    RIGHT_ARROW, // ->
};

union TokenValue {
    Sym8 None;
    Sym8 *Identifier;
    Bit64 Machine;
    Nat64 Natural;
    Int64 Integer;
    Real64 Real;
    const Sym8 *Text;
};

struct Token {
    U::Point Start;
    U::Point End;
    TokenID ID;
    TokenValue Value;

public:
    Void Destroy();
};

#endif // KC_ANALYZER_TOKEN_H
