#ifndef KPLC_ANALYZER_TOKEN_CPP
#define KPLC_ANALYZER_TOKEN_CPP

#include "../Definitions.cpp"

struct Token {
    struct Point {
        Nat64 Line;
        Nat64 Column;
    };

    enum class Symbol : Nat16 {
        None = 0,
        End,

        OpenBrace = '{',
        CloseBrace = '}',
        OpenParen = '(',
        CloseParen = ')',
        OpenBracket = '[',
        CloseBracket = ']',
        Lesser = '<',
        Greater = '>',
        Quote = '\"',
        Comma = ',',
        Colon = ':',
        Semicolon = ';',
        Equal = '=',
        Add = '+',
        Minus = '-',
        Exclaim = '!',
        Question = '?',
        At = '@',
        And = '&',
        Or = '|',
        Not = '!',

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

        DoubleColon, // ::
        RightArrow, // ->
        Increment, // ++
        Decrement, // --
        Equivalent, // ==
        LesserEquivalent, // <=
        GreaterEquivalent, // >=
        AND, // &&
        OR, // ||
    };

    union Value {
        Text8 None;
        const Text8 *Identity;
        Nat64 Natural;
        Int64 Integer;
        Real64 Real;
        Bit64 Machine;
        const Text8 *Text;
    };

public:
    Token::Point Start;
    Token::Point End;
    Token::Symbol Symbol;
    Token::Value Value;

public:
    Void Destroy() {
        switch (this->Symbol) {
        case Token::Symbol::Identity:
            delete[] this->Value.Identity;
            return;
        case Token::Symbol::Text:
            delete[] this->Value.Text;
            return;
        default:
            return;
        }
    }
};

#endif // KPLC_ANALYZER_TOKEN_CPP
