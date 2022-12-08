#ifndef KPLC_ANALYZER_PARSER_CPP
#define KPLC_ANALYZER_PARSER_CPP

#include "Lexer.cpp"

#include "../Syntax/Identifier.cpp"

enum class ParserState {

};

class Parser {
    U::Dynar<Symbol> symbols;

public:
    Parser()
    {}

    template<typename Syntax_T>
    Syntax_T Parse();
};

#endif // KPLC_ANALYZER_PARSER_CPP

