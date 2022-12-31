#ifndef KC_ANALYZER_LEXER_HPP
#define KC_ANALYZER_LEXER_HPP

#include "token.hpp"

namespace KC {

class Lexer {
        const Sym *cursor;
        Location::Point point;

public:
        static constexpr const Nat16 BUFFER_SIZE= 1028 / 2;

public:
        explicit Lexer(const Sym *source);
        ~Lexer() = default;

public:
        Token lex();

private:
        constexpr Bool isOnSpaceSym() const noexcept {
                return (*this->cursor >= '\t' && *this->cursor <= '\r') ||
                        *this->cursor == ' ';
        }
        
        constexpr Bool isOnDigitSym() const noexcept {
                return *this->cursor >= '0' && *this->cursor <= '9';
        }

        constexpr Bool isOnIdentifierSym() const noexcept {
                return (*this->cursor >= 'A' && *this->cursor <= 'Z') ||
                       (*this->cursor >= 'a' && *this->cursor <= 'z');
        }

private:
        Void advance() noexcept;
};

} // namespace KC

#endif // KC_ANALYZER_LEXER_HPP
