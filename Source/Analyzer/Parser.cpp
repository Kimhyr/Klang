#ifndef KPLC_ANALYZER_PARSER_CPP
#define KPLC_ANALYZER_PARSER_CPP

#include "Lexer.cpp"

#include "../Syntax/Identifier.cpp"

enum class ParserState {

};

class Parser {
    U::Dynar<Symbol> symbols;
    Lexer lexer;
    Token token;

public:
    Parser(const Text8 *source)
        : lexer(source)
    {}

    template<typename Syntax_T>
    Syntax_T Parse();

    template<>
    S::Procedure Parse() {

    }

    template<>
    S::Identifier Parse() {
        S::Identifier identifier;
        if (($ token = $ lexer.Lex()).Enum != TokenEnum::Identity)
            throw Exception(CompilerModule::Parser, 0,
                            "Expected an Identity token.");
        identifier.Identity = token.Value.Identity;
        for ($ token = $ lexer.Lex(); $ token.Enum != TokenEnum::OpenParen &&
                                      $ token.Enum != TokenEnum::RightArrow &&
                                      $ token.Enum != TokenEnum::Semicolon;
             $ token = $ lexer.Lex()) {
            switch ($ token.Enum) {
            case TokenEnum::Question:
                if (identifier.Flag.Check(S::IdentifierFlag::Mutable))
                    throw Exception(CompilerModule::Parser, 0,
                                    "Expected a single question token, but received multiple.");
                identifier.Flag.Set(S::IdentifierFlag::Mutable);
                break;
            default:
                throw Exception(CompilerModule::Parser, 0,
                                "Expected an identifier modifier token.");
            }
        }
        return identifier;
    }

    template<>
    S::Cast Parse() {
        S::Cast cast;
        while (($ token = $ lexer.Lex()).Enum == TokenEnum::At)
            ++cast.PointerCount;
        // TODO
    }

    template<>
    S::Datum Parse() {
    }


    template<>
    S::Body Parse() {}

private:
};

#endif // KPLC_ANALYZER_PARSER_CPP

