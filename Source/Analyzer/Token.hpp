#pragma once
#ifndef ANALYER_TOKEN_HPP
#define ANALYER_TOKEN_HPP

#include "../Core.hpp"
#include "../Utils/Structs.hpp"

struct LiteralT {
  enum struct Flag {
    Cooked, // Escapable string/character | Signed integer
    Bit8,
    Bit16,
    Bit32,
    Bit64,
    Bit128,
  };

  enum struct Kind {
    Integer,
    Float,
    Character,
    String,
  };

  LiteralT::Flag flags;
  LiteralT::Kind kind;
  const Char8 *value;
};

enum struct KeywordT {
  Procedure,
  Datum,
  Return,
};

enum struct PunctuatorT {
  OParen = '(',
  CParen = ')',
  OCurl = '{',
  CCurl = '}',
  Comma = ',',
  Semicolon = ';',
};

enum struct OperT {
  Equal = '=',
  Plus = '+',
  Minus = '-',
  DColon = 256, // ::
  RArrow, // ->
};

enum struct ModifierT {
  Slosh = '\\',
  At = '@',
  Question = '?',
};

struct Token {
  enum struct Kind {
    None,
    Identifier,
    Keyword,
    Literal,
    Punctuator,
    Oper,
    Modifier,
  };

  union Value {
    const Char8 *Identifier;
    KeywordT Keyword;
    LiteralT Literal;
    PunctuatorT Punctuator;
    OperT Oper;
    ModifierT Modifier;
  };

  const Char8 *path;
  Point start;
  Point end;
  Token::Kind kind;
  Token::Value value;

  constexpr const Char8 *KindToStr() {
    switch (this->kind) {
    case Kind::None:
      return "None";
    case Kind::Identifier:
      return "Identifier";
    case Kind::Keyword:
      return "Keyword";
    case Kind::Literal:
      return "Literal";
    case Kind::Punctuator:
      return "Punctuator";
    case Kind::Oper:
      return "Oper";
    case Kind::Modifier:
      return "Modifier";
    }
  }
};

#endif  // ANALYER_TOKEN_HPP
