#pragma once
#ifndef ANALYER_TOKEN_HPP
#define ANALYER_TOKEN_HPP

#include "Lexer.hpp"

struct Token {
  enum struct Flag : UInt8 {
    Error = 0x01,
    EoF = 0x02,
    Switch = 0x04,
  };

  virtual Token::Flag Lex(Lexer *lexer);
};

struct IdentifierT : public Token {
  const Char8 *identifier;

  Void Destroy();
  Token::Flag Lex(Lexer *lexer);
};

struct LiteralT : public Token {
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
  Token::Flag Lex(Lexer *lexer);
};

struct KeywordT : public Token {
  enum struct Value {
    Procedure,
    Datum,
    Return,
  };

  KeywordT::Value value;

  Token::Flag Lex(Lexer *lexer);
};

struct OperT : public Token {
  enum struct Value {
    Equal = '=',
    Plus = '+',
    Minus = '-',
    DColon = 256,  // ::
    RArrow,        // ->
  };

  OperT::Value value;

  Token::Flag Lex(Lexer *lexer);
};

struct PunctuatorT : public Token {
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

  Token::Flag Lex(Lexer *lexer);
};

struct ModifierT : public Token {
  enum Value {
    At = '@',
    Question = '?',
    Slosh = '\\',
  };

  ModifierT::Value value;

  Token::Flag Lex(Lexer *lexer);
};

#endif  // ANALYER_TOKEN_HPP
