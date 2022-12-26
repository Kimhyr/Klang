#ifndef _LEXER_HPP
#define _LEXER_HPP

#include "../utilities/buffer.hpp"
#include "token.hpp"

namespace KC {

class Lexer {
        const Sym *cursor;
        Location::Point point;

public:
        static constexpr const Nat16 MAX_IDENTIFIER_LENGTH = 1028;
        static constexpr const Nat8 MAX_NUMBER_LENGTH = 64 * 2;

public:
        explicit Lexer(const Sym *path);
        ~Lexer() = default;

public:
        Token lex();

private:
        Void lexNatural(Buffer<Sym, Lexer::MAX_NUMBER_LENGTH> *buffer);

private:
        constexpr Bool checkIfDigit() {
                return *this->cursor >= '0' && *this->cursor <= '9';
        }

        constexpr Bool checkIfNatural() {
                return this->checkIfDigit() || *this->cursor == '_';
        }

        constexpr Bool checkIfIdentifier() {
                return (*this->cursor >= 'A' && *this->cursor <= 'Z') ||
                       (*this->cursor >= 'a' && *this->cursor <= 'z') ||
                        *this->cursor == '_';
        }

        constexpr Bool checkIfHexadecimal() {
                return (*this->cursor >= 'A' && *this->cursor <= 'F') ||
                       (*this->cursor >= 'a' && *this->cursor <= 'f') ||
                        this->checkIfDigit();
        }

        constexpr Bool checkIfBinary() {
                return *this->cursor == '0' || *this->cursor == '1' ||
                       *this->cursor == '_';
        }

private:
        Void advance();
};

} // namespace KC

#endif // _LEXER_HPP
