#pragma once
#ifndef ANALYZER_PARSER_HPP
#define ANALYZER_PARSER_HPP

#include "../Utils/Dynarray.hpp"
#include "Syntax.hpp"
#include "Lexer.hpp"

struct Parser {
    ErrorBuffer *errBuf;
    Lexer lexer;
    Dynarray<O::Declaration> identifiers;
    enum struct Flag {
        EoF = 0x01,

        Done = 0x02,
    } flags;
    enum struct State {
        SkipToTerminator,
        Done,
    } state;
    Token token;
    
    Parser(ErrorBuffer *errBuf, const Char8 *source);
    Void Parse();
    Parser::Flag Advance();
};

#endif  // ANALYZER_PARSER_HPP
