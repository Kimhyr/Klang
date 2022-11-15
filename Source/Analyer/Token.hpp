#pragma once
#ifndef ANALYER_TOKEN_HPP
#define ANALYER_TOKEN_HPP

#include "../Utils/Structs.hpp"
#include "../Core.hpp"

struct IdentifierT {
  const Char8 *identifier;

  Void Destroy();
};

struct LiteralT {
  enum Flag : UInt8 {
    Bit16 = 0x01,
    Bit32 = 0x02,
    Bit64 = 0x04,
    Bit128 = 0x08,
    Signed = 0x10,
    Cooked = 0x20,
  };

  enum struct Kind : UInt8 {
    Void,
    Integer,
    Float,
    Character,
    String,
  };

  union Value {
    UInt64 Integer;
    Float128 Float;
    Char16 Character;
    Char16 *String;
  };

  LiteralT::Flag flags;
  LiteralT::Kind kind;
  LiteralT::Value vlaue;

  Void Destroy();
};

struct KeywordT {
  enum struct Value {
    Procedure,
    Datum,
    Return,
  };

  KeywordT::Value value;

};

struct OperT {
  enum struct Value {
    Equal = '=',
    Plus = '+',
    Minus = '-',
    DColon = 256,  // ::
    RArrow,        // ->
  };

  OperT::Value value;

};

struct PunctuatorT {
  enum struct Value {
    Semicolon = ';',
    Apostrophe = '\'',
    OParen = '(',
    CParen = ')',
    OBrace = '{',
    CBrace = '}',
    Comma = ',',
    FArrow = 256,  // =>
  };

  PunctuatorT::Value value;

};

struct ModifierT {
  enum Value {
    At = '@',
    Question = '?',
    Slosh = '\\',
  };

  ModifierT::Value value;

};

struct Token {
  enum struct Kind {
    Identifeir,
    Literal,
    Keyword,
    Oper,
    Punctuator,
    Modifier,
  };

  union Value {
    IdentifierT Identifier;
    LiteralT Literal;
    KeywordT Keyword;
    OperT Oper;
    PunctuatorT Punctuator;
    ModifierT Modifier;
  };

  const Char8 *path;
  Point start;
  Point end;
  Token::Kind kind;
  Token::Value value;
};

#endif  // ANALYER_TOKEN_HPP
