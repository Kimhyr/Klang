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

  enum struct Keyword {
    Procedure,
    Datum,
    Return,
  };

  enum struct Punctuator {
    OParen = '(',
    CParen = ')',
    OCurl = '{',
    CCurl = '}',
    Comma = ',',
    Semicolon = ';',
  };

  enum struct Oper {
    Equal = '=',
    Plus = '+',
    Minus = '-',
    DColon = 256,  // ::
    RArrow,        // ->
  };

  enum struct Modifier {
    Slosh = '\\',
    At = '@',
    Question = '?',
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
    Keyword,
    Literal,
    Punctuator,
    Oper,
    Modifier,
  } kind;
  union Value {
    const Char8 *Identifier;
    T::Keyword Keyword;
    T::Literal Literal;
    T::Punctuator Punctuator;
    T::Oper Oper;
    T::Modifier Modifier;
  } value;

  constexpr const Char8 *KeywordToStr() {
    switch (this->value.Keyword) {
    case T::Keyword::Procedure:
      return "KeywordT::Procedure";
    case T::Keyword::Datum:
      return "KeywordT::Datum";
    case T::Keyword::Return:
      return "KeywordT::Return";
    }
  }

  constexpr const Char8 *PunctuatorToStr() {
    switch (this->value.Punctuator) {
    case T::Punctuator::OParen:
      return "PunctuatorT::OParen";
    case T::Punctuator::CParen:
      return "PunctuatorT::CParen";
    case T::Punctuator::OCurl:
      return "PunctuatorT::OCurl";
    case T::Punctuator::CCurl:
      return "PunctuatorT::CCurl";
    case T::Punctuator::Comma:
      return "PunctuatorT::Comma";
    case T::Punctuator::Semicolon:
      return "PunctuatorT::Semicolon";
    }
  }

  constexpr const Char8 *OperToStr() {
    switch (this->value.Oper) {
    case T::Oper::Equal:
      return "OperT::Equal";
    case T::Oper::Plus:
      return "OperT::Plus";
    case T::Oper::Minus:
      return "OperT::Minus";
    case T::Oper::DColon:
      return "OperT::DColon";
    case T::Oper::RArrow:
      return "OperT::RArrow";
    }
  }

  constexpr const Char8 *ModifierToStr() {
    switch (this->value.Modifier) {
    case T::Modifier::Slosh:
      return "ModifierT::Slosh";
    case T::Modifier::At:
      return "ModifierT::At";
    case T::Modifier::Question:
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
