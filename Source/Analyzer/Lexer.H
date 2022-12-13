#ifndef KC_ANALLYZER_LEXER_H
#define KC_ANALLYZER_LEXER_H

#include "../Doctor.H"
#include "../Utilities/Text.H"
#include "../Utilities/Dynar.H"
#include "../Utilities/Result.H"
#include "Token.H"

enum class LexerModule : Nat8 {
    ALPHABETIC,
    NUMERIC,
    NATURAL,
    BINARY,
    HEXADECIMAL,
    REAL,
    SCIENTIFIC,
    SYMBOLIC,
};

enum class LexerFlag : Bit8 {
    END = 1 << 0,
    CONTINUE = 1 << 1,
};

enum class LexerError : Nat8 {
    WRONG_FORMAT,
    INCOMPLETE,
    INCONVERTABLE,
    OUT_OF_RANGE,
};

class Lexer {
    U::Point point;
    Int64 index;
    const Sym8 *source;
    Sym8 peek;
    Token token;

public:
    explicit constexpr
    Lexer(const Sym8 *source)
        : point({1, 1}),
          index(-1),
          source(source),
          peek(*source),
          token() {}

    Void Destroy();

public:
    U::Result<Token> Lex();
};

#endif // KC_ANALLYZER_LEXER_H
