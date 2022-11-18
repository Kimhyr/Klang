#pragma once
#ifndef ANALYZER_LEXER_HPP
#define ANALYZER_LEXER_HPP

#include "../Utils/Error.hpp"
#include "../Utils/String.hpp"
#include "Token.hpp"

struct Lexer {
  ErrorBuffer *errBuf;
  UInt64 index;
  const Char8 *source;
  Char8 peek;
  Token::Point point;
  enum struct Flag {
    EoF = (1 << 0),
    Error = (1 << 1),
    Continue = (1 << 2),
  } flags;
  String buffer;

  Lexer(ErrorBuffer *errBuf, const Char8 *source);
  Void Destroy();

  Lexer::Flag Lex(Token *out);

  constexpr Char8 Peek(Char8 offset = 1) {
    return this->source[this->index + offset];
  }
  Void Advance();
};

#endif  // ANALYZER_LEXER_HPP
