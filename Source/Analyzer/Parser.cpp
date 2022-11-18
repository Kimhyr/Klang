#include "Parser.hpp"
#include "../Utils/Bit.hpp"

Parser::Parser(ErrorBuffer *errBuf, const Char8 *source)
    : errBuf(errBuf)
    , lexer(errBuf, source) {}

Void Parser::Parse() {
    Parser::Flag flags = this->Advance();
}

Parser::Flag Parser::Advance() {
    Lexer::Flag lexerFlags;
    UInt8 flags;
LOOP_START:
    lexerFlags = this->lexer.Lex(&this->token);
    if (Bit::Bit_0(lexerFlags)) {
        flags |= (UInt8)Parser::Flag::EoF;
        this->flags = (Parser::Flag)flags;
        if (Bit::Bit_1(this->flags)) {
            this->state = Parser::State::Done;
        }
        goto LOOP_END;
    }
    if (Bit::Bit_1(lexerFlags)) {
        this->state = Parser::State::SkipToTerminator;
        // Error
    }
    if (Bit::Bit_2(lexerFlags)) {
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
