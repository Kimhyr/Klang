#pragma once
#ifndef ANALYER_TOKEN_HPP
#define ANALYER_TOKEN_HPP

#include "../Core.hpp"

struct LiteralT {
  enum struct Flag : UInt8 {
    Signed = 0x01,
    // 0x02
    Cooked = 0x04,
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
  struct Point {
    UInt64 row;
    UInt64 column;

    const Char8 *ToStr();
  } start;
  Token::Point end;
  enum struct Kind {
    None,
    Identifier,
    Keyword,
    Literal,
    Punctuator,
    Oper,
    Modifier,
  } kind;
  union Value {
    const Char8 *Identifier;
    KeywordT Keyword;
    LiteralT Literal;
    PunctuatorT Punctuator;
    OperT Oper;
    ModifierT Modifier;
  } value;

  constexpr const Char8 *KeywordToStr() {
    switch (this->value.Keyword) {
    case KeywordT::Procedure:
      return "KeywordT::Procedure";
    case KeywordT::Datum:
      return "KeywordT::Datum";
    case KeywordT::Return:
      return "KeywordT::Return";
    }
  }

  constexpr const Char8 *PunctuatorToStr() {
    switch (this->value.Punctuator) {
      case PunctuatorT::OParen:
        return "PunctuatorT::OParen";
      case PunctuatorT::CParen:
        return "PunctuatorT::CParen";
      case PunctuatorT::OCurl:
        return "PunctuatorT::OCurl";
      case PunctuatorT::CCurl:
        return "PunctuatorT::CCurl";
      case PunctuatorT::Comma:
        return "PunctuatorT::Comma";
      case PunctuatorT::Semicolon:
        return "PunctuatorT::Semicolon";
    }
  }

  constexpr const Char8 *OperToStr() {
    switch (this->value.Oper) {
    case OperT::Equal:
      return "OperT::Equal";
    case OperT::Plus:
      return "OperT::Plus";
    case OperT::Minus:
      return "OperT::Minus";
    case OperT::DColon:
      return "OperT::DColon";
    case OperT::RArrow:
      return "OperT::RArrow";
    }
  }

  constexpr const Char8 *ModifierToStr() {
    switch (this->value.Modifier) {
    case ModifierT::Slosh:
      return "ModifierT::Slosh";
    case ModifierT::At:
      return "ModifierT::At";
    case ModifierT::Question:
      return "ModifierT::Question";
    }
  }

  constexpr const Char8 *KindToStr() {
    switch (this->kind) {
    case Kind::None:
      return "Token::Kind::None";
    case Kind::Identifier:
      return "Token::Kind::Identifier";
    case Kind::Keyword:
      return "Token::Kind::Keyword";
    case Kind::Literal:
      return "Token::Kind::Literal";
    case Kind::Punctuator:
      return "Token::Kind::Punctuator";
    case Kind::Oper:
      return "Token::Kind::Oper";
    case Kind::Modifier:
      return "Token::Kind::Modifier";
    }
  }
  const Char8 *PointToStr();
  const Char8 *ToStr();
};

#endif  // ANALYER_TOKEN_HPP
