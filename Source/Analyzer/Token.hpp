#ifndef KPLC_ANALYZER_TOKEN_HPP
#define KPLC_ANALYZER_TOKEN_HPP

#include "../Definitions.hpp

namespace Analyzer {
    class Token {
    public: // Types
        struct Point {
            UInt64 Line;
            UInt64 Column;
        };

        enum class Symbol {
            None = 0,

            // Punctuates
            OParen = '(',
            CParen = ')',
            OBrace = '{',
            CBrace = '}',
            Comma = ',',
            Semicolon = ';',

            // Operators
            Equal = '=',
            Plus = '+',

            // Modifiers
            Question = '?',
            At = '@',

            // Words
            Identity = 256,
            Procedure,
            Let,
            Return,

            // Literals
            Integer,
            Real,
            Symbol,
            Text,

            // Punctuates

            // Operators
            Cast, // ::

            // Modifiers

        };

        // I know I can make the type into "Char8 *".
        union Value {
            Char8 None;
            Char8 *Identity;
            Char8 *Integer;
            Char8 *Real;
            Char8 Symbol;
            Char8 *Text;
        };

    public: // Constructors and destructors
        constexpr
        Token() = default;

        explicit constexpr
        Token(Token::Point start)
                : start(start) {}

        inline
        Void Destroy();

    public: // Properties
        inline constexpr
        const Token::Point *GetStart()
        const noexcept { return &this->start; }

        inline constexpr
        Void SetStart(Token::Point start)
        const noexcept { this->start = start; }

        inline constexpr
        const Token::Point *GetEnd()
        const noexcept { return &this->end; }

        inline constexpr
        Void SetEnd(Token::Point end)
        const noexcept { this->end = end; }

        inline constexpr
        Token::Symbol GetSymbol()
        const noexcept { return &this->symbol; }

        inline constexpr
        Void SetSymbol(Token::Symbol symbol)
        const noexcept { this->symbol = symbol; }

        inline constexpr
        const Token::Value *GetValue()
        const noexcept { return &this->value; }

        inline constexpr
        Void SetValue(Token::Value value)
        const noexcept { this->value = value; }

    private: // Members
        Token::Point start;
        Token::Point end;
        Token::Symbol symbol;
        Token::Value value;
    };
} // Analyzer

#endif // KPLC_ANALYZER_TOKEN_HPP
