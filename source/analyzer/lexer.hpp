#ifndef KC_LEXER_HPP
#define KC_LEXER_HPP

#include "../utilities/buffer.hpp"
#include "token.hpp"

namespace KC {

class Lexer {
        const Sym *cursor;
        Location::Point point;

public:
        static constexpr const Nat16 BUFFER_SIZE= 1028 / 2;

public:
        explicit Lexer(const Sym *path);
        ~Lexer() = default;

public:
        Token lex();

private:
        Void lexNaturalAndReal(Buffer<Sym, Lexer::BUFFER_SIZE> *buffer, Token *token);

        inline Void lexIdentifier(Buffer<Sym, Lexer::BUFFER_SIZE> *buffer);
        inline Void lexBinary(Buffer<Sym, Lexer::BUFFER_SIZE> *buffer);
        inline Void lexHexadecimal(Buffer<Sym, Lexer::BUFFER_SIZE> *buffer);

private:
        constexpr Bool isOnDigitSym() const noexcept {
                return *this->cursor >= '0' && *this->cursor <= '9';
        }

        constexpr Bool isOnIdentifierSym() const noexcept {
                return (*this->cursor >= 'A' && *this->cursor <= 'Z') ||
                       (*this->cursor >= 'a' && *this->cursor <= 'z');
        }

        constexpr Bool isOnHexadecimalSym() const noexcept {
                return (*this->cursor >= 'A' && *this->cursor <= 'F') ||
                       (*this->cursor >= 'a' && *this->cursor <= 'f') ||
                        this->isOnDigitSym();
        }

        constexpr Bool isOnBinarySym() const noexcept{
                return *this->cursor == '0' || *this->cursor == '1';
        }

private:
        Void advance() noexcept;
};

} // namespace KC

#endif // KC_LEXER_HPP
