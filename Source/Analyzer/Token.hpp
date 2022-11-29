#ifndef KPLC_ANALYZER_TOKEN_HPP
#define KPLC_ANALYZER_TOKEN_HPP

#include "../Definitions.hpp"

namespace Analyzer {
    class Token {
    public: // Types
        struct Point {
            UInt64 Line;
            UInt64 Column;

            constexpr
            Void Set(Token::Point point)
            noexcept {  *this = point; }
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
            String,

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
            Char8 *String;
        };

    public: // Constructors and destructors
        Token() = default;

        explicit
        Token(Token::Point start)
                : start(start) {}

        Void Destroy();

    public: // Properties
        constexpr
        const Token::Point *GetStart()
        const noexcept { return &this->start; }

        constexpr
        Void SetStart(Token::Point start)
        noexcept { this->start= start; }

        constexpr
        const Token::Point *GetEnd()
        const noexcept { return &this->end; }

        constexpr
        Void SetEnd(Token::Point end)
        noexcept { this->end = end; }

        constexpr
        Token::Symbol GetSymbolCopy()
        const noexcept { return this->symbol; }

        constexpr
        Void SetSymbol(Token::Symbol symbol)
        noexcept { this->symbol = symbol; }

        constexpr
        const Token::Value *GetValue()
        const noexcept { return &this->value; }

        constexpr
        Void SetValue(Token::Value value)
        noexcept { this->value = value; }

    private: // Members
        Token::Point start;
        Token::Point end;
        Token::Symbol symbol;
        Token::Value value;
    };
} // Analyzer

#endif // KPLC_ANALYZER_TOKEN_HPP
