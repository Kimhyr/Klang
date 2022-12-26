#include "lexer.hpp"

#include <stdio.h>

namespace KC {

Lexer::Lexer(const Sym *source) :
    cursor(source), point({.row = 1, .column = 1}) {}

Token Lexer::lex() {
        Token token(this->point);
        return token;
}

Void Lexer::advance() {
        if (*(++this->cursor) == '\n') {
                ++this->point.row;
                this->point.column = 0;
        }
        ++this->point.column;
}


Void Lexer::lexNatural(Buffer<Sym, Lexer::MAX_NUMBER_LENGTH> *buffer) {
        do {
                if (*this->cursor != '_')
                        buffer->put(*this->cursor);
                this->advance();
        } while (this->checkIfNatural());
}

} // namespace KC
