#ifndef KPLC_ANALYZER_LEXER_HPP
#define KPLC_ANALYZER_LEXER_HPP

#include "../Definitions.hpp"
#include "../Module.hpp"
#include "Token.hpp"

namespace Analyzer {
    class Lexer : Compiler::Module {
    public:
        enum Flag : Bit8 {
            End = 1 << 0,
            Continue = 1 << 1,
        };

    public: // Constructors and destructors
        constexpr
        Lexer(const Char8 *source)
                : flags(0),
                  point(1, 1),
                  index(-1),
                  source(source),
                  peek(source[0]) {}
        inline
        Void Destroy();

    public: // Procedures
        Lexer::Flag Lex(Token *out);

    public: // Procedures from Compiler::Module
        inline constexpr
        const Char8 *GetModuleName()
        const noexcept { return "Lexer"; }

    private: // Properties
        Lexer::Flag flags;
        Token::Point point;
        Int64 index;
        const Char8 *source;
        Char8 peek;

    private: // Procedures
        inline constexpr
        Char8 Peek(UInt64 offset = 1)
        const noexcept {
            return this->source[this->index + offset];
        }

        inline constexpr
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
