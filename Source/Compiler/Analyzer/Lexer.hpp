#ifndef KPLC_COMPILER_ANALYZER_LEXER_HPP
#define KPLC_COMPILER_ANALYZER_LEXER_HPP

#include "../../Utility/Text/Char.hpp"
#include "../../Utility/Collections/Dynar.hpp"
#include "../../Definitions.hpp"
#include "Token.hpp"

namespace Compiler::Analyzer {
    using namespace Compiler;
    using namespace Utility;
    using namespace Utility::Text;
    using namespace Utility::Collections;

    class Lexer {
    public:
        enum Flag : Bit8 {
            None = 0,
            End = 1 << 0,
            Continue = 1 << 1,
        };

        enum class ErrorCode : Nat8 {
            WrongFormat = 1,
            Valueless,
            Incomplete,
            Conversion,
            OutOfRange,
        };

    public:
        [[nodiscard]]
        explicit constexpr
        Lexer(const Text8 *source)
            : flags(Lexer::Flag::None),
              point({1, 1}),
              index(-1),
              source(source),
              peek(source[0]),
              token() {}

        Void Destroy();

    public:
        [[nodiscard]]
        constexpr
        Bit8 GetFlags()
        const noexcept { return this->flags; }

    public:
        Token Lex();

    private:
        enum class Way : Nat8 {
            NumericLiteral = 1,
            NaturalLiteral,
            BinaryLiteral,
            HexadecimalLiteral,
            RealLiteral,
        };

    private:
        Bit8 flags;
        Token::Point point;
        Int64 index;
        const Text8 *source;
        Text8 peek;
        Token token;

    private:
        inline
        Void LexAlphabetic()
        noexcept;

        inline
        Void MatchAlphabetic(const Text8 *flush)
        noexcept;

        inline
        Void LexNumeric();

        Void LexNaturalLiteral(Dynar<Text8> *buf);

        inline
        Void PutNumericBuf(Dynar<Text8> *buf);

        [[nodiscard]]
        constexpr
        Bool PeekIsValidUnsigned()
        const noexcept { return Char::IsNumeric(this->peek) || this->peek == '_'; }

        inline
        Void LexBinaryLiteral(Dynar<Text8> *buf);

        [[nodiscard]]
        constexpr
        Bool PeekIsValidBinary()
        const noexcept { return this->peek == '0' || this->peek == '1' || this->peek == '_'; }

        inline
        Void LexHexadecimalLiteral(Dynar<Text8> *buf);

        [[nodiscard]]
        constexpr
        Bool PeekIsValidHexadecimal()
        const noexcept {
            return Char::IsNumeric(this->peek) || (this->peek >= 'a' && this->peek <= 'f') ||
                   (this->peek >= 'A' && this->peek <= 'F') || this->peek == '_';
        }

        inline
        Void LexReal(Dynar<Text8> *buf);

        inline
        Void SkipZeros()
        noexcept;

        inline
        Void LexSymbolic();

        inline
        Void SkipWhitespace();

        static
        Void ThrowException(Lexer::Way way, Lexer::ErrorCode error);

        [[nodiscard]]
        constexpr
        Text8 Peek(Nat64 offset = 1)
        const noexcept { return this->source[this->index + offset]; }

        constexpr
        Void Advance()
        noexcept {
            this->index++;
            this->peek = this->Peek();
            if (this->peek == '\n') {
                this->point.Line++;
                this->point.Column = 0;
            }
            this->point.Column++;
        }
    };
} // Analyzer

#endif // KPLC_COMPILER_ANALYZER_LEXER_HPP
