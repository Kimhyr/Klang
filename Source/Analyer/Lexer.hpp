#pragma once
#ifndef ANALYER_LEXER_HPP
#define ANALYER_LEXER_HPP

#include "../Core.hpp"
#include "../Utils/Structs.hpp"
#include "../Utils/Error.hpp"

struct Lexer {
  ErrorBuffer *errBuf;
  UInt64 index;
  const Char8 *source;
  Point point;

  Lexer(ErrorBuffer *errBuf, const Char8 *source);
  constexpr Char8 Peek(UInt64 offset = 1) {
    return this->source[this->index + offset];
  }
  Void Advance();
};

#endif  // ANALYER_LEXER_HPP
