#ifndef KPLC_ANALYZER_LEXER_HPP
#define KPLC_ANALYZER_LEXER_HPP

#include "../Utility/Char.hpp"
#include "../Utility/Dynar.hpp"
#include "../Definitions.hpp"
#include "../Module.hpp"
#include "Token.hpp"

namespace Analyzer {
    using namespace Utility;

    class Lexer : public Compiler::Module {
    public: // Types
        enum Flag : Bit8 {
            None = 0,
            End = 1 << 0,
            Continue = 1 << 1,
        };

        enum class ErrorCode {
            BinaryNumber,
        };

    public: // Constructors and destructors
        constexpr
        Lexer(const Char8 *source)
                : flags(Lexer::Flag::None),
                  point({1, 1}),
                  index(-1),
                  source(source),
                  peek(source[0]),
                  token() {}
        inline
        Void Destroy();

    public: // Properties
        inline constexpr
        Bit8 GetFlagsCopy()
        const noexcept { return this->flags; }

    public: // Procedures
        Token Lex();

    public: // Procedures from Compiler::Module
        inline
        Module::Identity GetModuleIdentity()
        const noexcept override { return Module::Identity::Lexer; }

    private: // Properties
        Bit8 flags;
        Token::Point point;
        Int64 index;
        const Char8 *source;
        Char8 peek;
        Token token;

    private: // Procedures
        static constexpr
        Bool CharIsHexNumber(Char8 in)
        noexcept { return Char::IsNumeric(in) || (in >='a' && in <= 'z') || (in >= 'A' && in <= 'Z'); }

        static constexpr
        Bool CharIsBinaryNumber(Char8 in)
        noexcept { return in == '0' || in == '1'; }

        static constexpr
        Bool CharIsNaturalNumber(Char8 in)
        noexcept { return Char::IsNumeric(in) || in == '_'; }

        Void LexNaturalNumber(Dynar<Char8> *buf);
        inline constexpr
        Char8 Peek(UInt64 offset = 1)
        const noexcept { return this->source[this->index + offset]; }

        constexpr
        Void Advance()
        noexcept {
            this->peek = this->Peek();
            if (this->peek == '\n') {
                this->point.Line++;
                this->point.Column = 0;
            }
            this->point.Column++;
            this->index++;
        }
    };
} // Analyzer

#endif // KPLC_ANALYZER_LEXER_HPP
