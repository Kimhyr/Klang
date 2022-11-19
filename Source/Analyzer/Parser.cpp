#include "Parser.hpp"

#include "../Utils/Bit.hpp"


Parser::Parser(ErrorBuffer *errBuf, const Char8 *source)
    : errBuf(errBuf)
    , lexer(errBuf, source) {
}

Void Parser::Parse() {

}

Void Parser::Advance() {

}
