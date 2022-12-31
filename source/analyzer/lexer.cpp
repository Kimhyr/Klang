#include "lexer.hpp"
#include "../utilities/buffer.hpp"

#include <string.h>

namespace KC {

Lexer::Lexer(const Sym *source)
        : cursor(source), point({.row = 1, .column = 1}) {}

Token Lexer::lex() {
        while (this->isOnSpaceSym())
                this->advance();
        Token token(this->point);
        switch ((Token::Tag)*this->cursor) {
        case Token::Tag::OPEN_PAREN:
        case Token::Tag::CLOSE_PAREN:
        case Token::Tag::COLON:
        case Token::Tag::SEMICOLON:
        case Token::Tag::SLOSH:
        case Token::Tag::EQUAL:
        case Token::Tag::PLUS:
        case Token::Tag::MINUS:
        case Token::Tag::ASTERISKS:
        case Token::Tag::SLASH:
        case Token::Tag::PERCENT:
        case Token::Tag::END:
                token.tag = (Token::Tag)*this->cursor;
                this->advance();
                break;
        default:
                Buffer<Sym, Lexer::BUFFER_SIZE> buffer;
                if (this->isOnIdentifierSym()) {
                        token.tag = Token::Tag::IDENTIFIER;
                        do {
                                buffer.put(*this->cursor);
                                this->advance();
                        } while (this->isOnIdentifierSym() || *this->cursor == '_');
                        try { buffer.put(0); }
                        catch (Result) { throw Diagnosis(); }
                        if (strcmp(buffer.getData(), "datum") == 0)
                                token.tag = Token::Tag::DATUM;
                        else token.value = buffer.flush();
                } else if (this->isOnDigitSym()) {
                        token.tag = Token::Tag::NATURAL;
                        do {
                                if (*this->cursor != '_')
                                        buffer.put(*this->cursor);
                                this->advance();
                        } while (this->isOnDigitSym() || *this->cursor == '_');
                        try { buffer.put(0); }
                        catch (Result) { throw Diagnosis(); } 
                        token.value = buffer.flush();
                } else throw Diagnosis();
                break;
        }
        token.location.end = this->point;
        return token;
}

Void Lexer::advance() noexcept{
        if (*(++this->cursor) == '\n') {
                ++this->point.row;
                this->point.column = 0;
        }
        ++this->point.column;
}

} // namespace KC
