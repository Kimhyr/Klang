#pragma once
#ifndef ANALYER_LEXER_HPP
#define ANALYER_LEXER_HPP

#include "../Core.hpp"
#include "../Utils/Error.hpp"
#include "../Utils/String.hpp"
#include "../Utils/Structs.hpp"
#include "Token.hpp"

struct Lexer {
  enum struct Flag : UInt8 {
    Error = 0x01,
    EoF = 0x02,
    Switch = 0x04,
  };

  ErrorBuffer *errBuf;
  Point point;
  String buffer;
  Char8 peek;
  UInt64 index;
  const Char8 *source;
  const Char8 *sourcePath;

  Lexer(ErrorBuffer *errBuf, const Char8 *sourcePath, const Char8 *source);

  Lexer::Flag Lex(Token *out);
  Void LexWord(Token *out, UInt8 *flags);
  Void LexNumber(Token *out, UInt8 *flags);
  Void LexSymbol(Token *out, UInt8 *flags);

  Void Advance();
  constexpr Char8 Peek(UInt64 offset = 1) {
    return this->source[this->index + offset];
  }

  static constexpr Bool HasError(Lexer::Flag flag) {
    return ((UInt8)flag | 0xfe) ^ 0xfe;
  }
  static constexpr Bool HasEoF(Lexer::Flag flag) {
    return ((UInt8)flag | 0xfd) ^ 0xfd;
  }
  static constexpr Bool HasSwitch(Lexer::Flag flag) {
    return ((UInt8)flag | 0xfb) ^ 0xfb;
  }
};

#endif  // ANALYER_LEXER_HPP
