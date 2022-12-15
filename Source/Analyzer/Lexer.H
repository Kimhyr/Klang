#ifndef KC_ANALLYZER_LEXER_H
#define KC_ANALLYZER_LEXER_H

#include "../Utilities/Table.H"
#include "../Utilities/Text.H"
#include "../Utilities/Buffer.H"
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
    Point point;
    Int64 index;
    const Sym8 *source;
    Sym8 peek;

public:
    static
    Table<const Sym8 *, Sym8, 3> KEYWORD_TABLE;

    static constexpr
    const Nat16 MAX_IDENTIFIER_LENGTH = 1028;

    static constexpr
    const Nat8 MAX_NUMBER_LENGTH = 64;

public:
    explicit constexpr
    Lexer(const Sym8 *source)
        : point({1, 0}),
          index(-1),
          source(source),
          peek(*source) {}

    Void Destroy();

public:
    Result Lex(Token *token);

private:
    Void LexNatural(const Buffer<Sym8, Lexer::MAX_NUMBER_LENGTH> *buffer, Token *token);

private:
    constexpr
    Sym8 Peek(Size offset = 1)
    const {
        return $ source[$ index + offset];
    }

    constexpr
    Void Advance() {
        ++$ index;
        $ peek = $ Peek();
        if ($ peek == '\n') {
            ++$ point.Row;
            $ point.Column = 0;
        }
        ++$ point.Column;
    }
};

#endif // KC_ANALLYZER_LEXER_H
