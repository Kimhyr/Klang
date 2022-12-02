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
            UInt64 Line;
            UInt64 Column;

            constexpr
            Void Set(Token::Point point)
            noexcept { *this = point; }
        };

        enum class Symbol {
            None = 0,

            // Delimiters
            OpenBraceDelimiter = '{',
            CloseBraceDelimiter = '}',
            OpenParenDelimiter = '(',
            CloseParenDelimiter = ')',
            OpenBracketDelimiter = '[',
            CloseBracketDelimiter = ']',
            OpenAngleDelimiter = '<',
            CloseAngleDelimiter = '>',
            Quote = '\"',

            // Punctuates
            CommaPunctuator = ',',
            SemicolonPunctuator = ';',

            // Operators
            AssignOperator = '=',
            AddOperator = '+',
            MinusOperator = '-',

            // Modifiers
            ExclaimModifier = '!',
            QuestionModifier = '?',
            AtModifier = '@',

            // Words
            Identity = 256,
            NamespaceKeyword,
            EnumerareKeyword,
            StructureKeyword,
            UnistructKeyword,
            ImplementKeyword,
            ProcedureKeyword,
            MacroKeyword,
            DatumKeyword,
            LabelKeyword,
            AliasKeyword,
            MatchKeyword,
            CaseKeyword,
            LoopKeyword,
            IfKeyword,
            ElifKeyword,
            ElseKeyword,
            GiveKeyword, // Return
            StopKeyword, // Break
            DropKeyword, // Next case
            RollKeyword, // Continue
            YeetKeyword, // Throw

            // Literals
            NaturalLiteral,
            IntegerLiteral,
            RealLiteral,
            MachineLiteral,
            TextLiteral,

            // Operators
            CastOperator, // ::
            ReturnOperator, // ->
            IncrementOperator, // ++
            DecrementOperator, // --
            EQOperator, // ==
            LEQOperator, // <=
            GEQOperator, // >=
            ANDOperator, // &&
            OROperator, // ||
            Space
        };

        // I know I can make the type into "Char8 *".
        union Value {
            Char8 None;
            const Char8 *Identity;
            UInt64 Natural;
            Int64 Integer;
            Float64 Float;
            Bit64 Machine;
            const Char8 *Text;
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
