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

struct Token {
public:
    using IDType = Sym8;

public:
    enum : IDType {
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

public:
    Point Start;
    Point End;
    IDType ID;
    union {
        Sym8 None;
        Sym8 *Identifier;
        Bit64 Machine;
        Nat64 Natural;
        Int64 Integer;
        Real64 Real;
        const Sym8 *Text;
    } Value;

public:
    Void Destroy();
};

#endif // KC_ANALYZER_TOKEN_H
