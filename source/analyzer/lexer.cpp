#include "lexer.hpp"

namespace KC {

Lexer::Lexer(const Sym *source)
        : cursor(source), point({.row = 1, .column = 1}) {}

Token Lexer::lex() {
        Token token(this->point);
        switch (*this->cursor) {
        case '0':
        default:
                if (this->isOnIdentifier()) {
                        token.tag = Token::Tag::IDENTIFIER;
                        Buffer<Sym, Lexer::MAX_IDENTIFIER_LENGTH> buffer;
                        do {
                                try { buffer.put(*this->cursor); }
                                catch (Int) { throw Diagnosis(); }
                                this->advance();
                        } while (this->isOnIdentifier());
                        try { buffer.put(0); }
                        catch (Bool) { throw Diagnosis(); } 
                        token.value = buffer.flush();
                        break;
                } else if (this->isOnDigit()) {
                        if (*this->cursor == '0') {
                                this->advance();
                                switch (*this->cursor) {
                                case 'X':
                                case 'x':
                                        break;
                                case 'B':
                                case 'b':
                                        break;
                                default:
                                        break;
                                }
                        }
                        token.tag = Token::Tag::NATURAL;
                        Buffer<Sym, Lexer::MAX_NUMBER_LENGTH> buffer;
                        this->lexNatural(&buffer);
                        try { buffer.put(0); }
                        catch (Bool) { throw Diagnosis(); } 
                        token.value = buffer.flush();
                        break;
                }
                throw Diagnosis();
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


Void Lexer::lexNatural(Buffer<Sym, Lexer::MAX_NUMBER_LENGTH> *buffer) {
        do {
                if (*this->cursor != '_') {
                        try { buffer->put(*this->cursor); }
                        catch(Bool) { throw Diagnosis(); }
                }
                this->advance();
        } while (this->isOnNatural());
}

} // namespace KC
