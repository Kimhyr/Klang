#ifndef KPLC_COMPILER_ANALYZER_TOKEN_HPP
#define KPLC_COMPILER_ANALYZER_TOKEN_HPP

#include "../../Definitions.hpp"

namespace Compiler::Analyzer {
    class Token {
    public:
        struct Point {
            UInt64 Line;
            UInt64 Column;

            constexpr
            Void Set(Token::Point point)
            noexcept {  *this = point; }
        };

        enum class Symbol {
            None = 0,

            // Delimiters
            OParenDelimiter  = '(',
            CParenDelimiter  = ')',
            OBraceDelimiter  = '{',
            CBraceDelimiter  = '}',

            // Punctuates
            CommaPunctuator = ',',
            SemicolonPunctuator = ';',

            // Operators
            EqualOperator = '=',
            PlusOperator = '+',

            // Modifiers
            QuestionModifier = '?',
            AtModifier = '@',

            // Words
            Identity = 256,
            ProcedureKeyword,
            LetKeyword,
            ReturnKeyword,

            // Literals
            UnsignedLiteral,
            SignedLiteral,
            FloatLiteral,
            MachineLiteral,
            TextLiteral,

            // Operators
            CastOperator, // ::
        };

        // I know I can make the type into "Char8 *".
        union Value {
            Char8 None;
            const Char8 *Identity;
            UInt64 Integer;
            Float64 Float;
            Bit64 Machine;
            const Char8 *Text;
        };

    public:
        Token() = default;

        explicit
        Token(Token::Point start)
                : start(start) {}

        Void Destroy();

    public:
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
        Token::Symbol GetSymbol()
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

    private:
        Token::Point start;

        Token::Point end;
        Token::Symbol symbol;
        Token::Value value;
    };
} // Analyzer

#endif // KPLC_COMPILER_ANALYZER_TOKEN_HPP
