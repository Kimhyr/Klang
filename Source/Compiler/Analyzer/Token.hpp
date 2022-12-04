#ifndef KPLC_COMPILER_ANALYZER_TOKEN_HPP
#define KPLC_COMPILER_ANALYZER_TOKEN_HPP

#include "../../Definitions.hpp"


/*
Primitives:
    Integers:
        Signed:
            - Nat8
            - Nat16
            - Nat32
            - Nat64
        Unsigned:
            - Int8
            - Int16
            - Int32
            - Int64
    Floats:
        - Float32
        - Float64
*/

namespace Compiler::Analyzer {
    class Token {
    public:
        struct Point {
            Nat64 Line;
            Nat64 Column;

            constexpr
            Void Set(Token::Point point)
            noexcept { *this = point; }
        };

        enum class Symbol : Nat16 {
            None = 0,

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

            Natural,
            Integer,
            Real,
            Machine,
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

        // I know I can make the type into "Text8 *".
        union Value {
            Text8 None;
            const Text8 *Identity;
            Nat64 Natural;
            Int64 Integer;
            Float64 Float;
            Bit64 Machine;
            const Text8 *Text;
        };

    public:
        Token() = default;

        explicit
        Token(Token::Point start)
            : start(start),
              end({}),
              symbol(Token::Symbol::None),
              value({}) {}

        Void Destroy();

    public:
        [[nodiscard]]
        constexpr
        const Token::Point *GetStart()
        const noexcept { return &this->start; }

        constexpr
        Void SetStart(Token::Point point)
        noexcept { this->start = point; }

        [[nodiscard]]
        constexpr
        const Token::Point *GetEnd()
        const noexcept { return &this->end; }

        constexpr
        Void SetEnd(Token::Point point)
        noexcept { this->end = point; }

        [[nodiscard]]
        constexpr
        Token::Symbol GetSymbol()
        const noexcept { return this->symbol; }

        constexpr
        Void SetSymbol(Token::Symbol tokenSymbol)
        noexcept { this->symbol = tokenSymbol; }

        [[nodiscard]]
        constexpr
        const Token::Value *GetValue()
        const noexcept { return &this->value; }

        constexpr
        Void SetValue(Token::Value tokenValue)
        noexcept { this->value = tokenValue; }

    private:
        Token::Point start;
        Token::Point end;
        Token::Symbol symbol;
        Token::Value value;
    };
} // Analyzer

#endif // KPLC_COMPILER_ANALYZER_TOKEN_HPP
