#pragma once
#ifndef ANALYER_TOKEN_HPP
#define ANALYER_TOKEN_HPP

#include "../Core.hpp"

namespace T {
  struct Literal {
    enum struct Flag : UInt8 {
      Signed = (1 << 0),
      // (1 << 1)
      Cooked = (1 << 2),
    } flags;
    enum struct Kind : UInt8 {
      Integer,
      Float,
      Character,
      String,
    } kind;
    const Char8 *value;

    const Char8 *ToStr();
  };

  enum struct Symbol {
    OParen = '(',
    CParen = ')',
    OCurl = '{',
    CCurl = '}',
    Comma = ',',
    Semicolon = ';',
    Colon = ':',
    Equal = '=',
    Plus = '+',
    Minus = '-',
    Slosh = '\\',
    At = '@',
    Question = '?',
    Procedure = 256,
    Datum,
    Return,
    DColon,  // ::
    RArrow,  // ->
  };
}  // namespace T

struct Token {
  struct Point {
    UInt64 row;
    UInt64 column;

    const Char8 *ToStr();
  } start;
  Token::Point end;
  enum struct Kind {
    None,
    Identifier,
    Literal,
    Symbol
  } kind;
  union Value {
    const Char8 *Identifier;
    T::Literal Literal;
    T::Symbol Symbol;
  } value;

  constexpr const Char8 *SymbolToStr() {
    return nil;
  }

  const Char8 *PointToStr();
  const Char8 *ToStr();
};

#endif  // ANALYER_TOKEN_HPP
