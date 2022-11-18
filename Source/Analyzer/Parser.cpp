#include "Parser.hpp"
#include "../Utils/Bit.hpp"

Parser::Parser(ErrorBuffer *errBuf, const Char8 *source)
    : errBuf(errBuf)
    , lexer(errBuf, source) {}

Void Parser::Parse() {
    this->Advance();
}

Void Parser::Advance() {
    Lexer::Flag lexerFlags = (Lexer::Flag)0;
LOOP_START:
    lexerFlags = this->lexer.Lex(&this->token);
    if (Bit::Check(lexerFlags, Lexer::Flag::EoF)) {
        Bit::Set(&this->flags, Parser::Flag::EoF);
        if (Bit::Check(this->flags, Lexer::Flag::Error)) {
            this->state = Parser::State::Done;
        }
        goto LOOP_END;
    }
    if (Bit::Check(lexerFlags, Lexer::Flag::Error)) {
        this->state = Parser::State::SkipToTerminator;
        // Error
    }
    if (Bit::Check(lexerFlags, Lexer::Flag::Continue)) {
        // Continue
    }
    switch (this->state) {
    case Parser::State::SkipToTerminator:
        goto LOOP_START;
    default:
        break;
    }
LOOP_END:
    return;
}
