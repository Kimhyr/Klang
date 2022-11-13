#pragma once
#ifndef ANALYER_TOKEN_HPP
#define ANALYER_TOKEN_HPP

#include "Lexer.hpp"

template<typename TReturn>
struct Token {
  enum struct Feed {
    Success,
    Error,
    EoF,
  };

  virtual Token::Feed Lex(Lexer *lexer, TReturn *out) = 0;
};

struct IdentifierT : public Token<IdentifierT> {
  const Char8 *identifier;

  Void Destroy();
  Token::Feed Lex(Lexer *lexer, IdentifierT *out);
};

struct LiteralT : public Token<LiteralT> {
  enum Flag : UInt8 {
    Bit16 = 0x01,
    Bit32 = 0x02,
    Bit64 = 0x04,
    Bit128 = 0x08,
    Signed = 0x10,
    Cooked = 0x20,
  };

  enum struct Kind : UInt8 {
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
  Token::Feed Lex(Lexer *lexer, LiteralT *out);
};

struct KeywordT : public Token<KeywordT> {
  enum struct Value {
    Procedure,
    Datum,
    Return,
  };

  KeywordT::Value value;

  Token::Feed Lex(Lexer *lexer, KeywordT *out);
};

struct OperT : public Token<OperT> {
  enum struct Value {
    Equal = '=',
    Plus = '+',
    Minus = '-',
    DColon = 256,  // ::
    RArrow,        // ->
  };

  OperT::Value value;

  Token::Feed Lex(Lexer *lexer, OperT *out);
};

struct PunctuatorT : public Token<PunctuatorT> {
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

  Token::Feed Lex(Lexer *lexer, PunctuatorT *out);
};

struct ModifierT : public Token<ModifierT> {
  enum Value {
    At = '@',
    Question = '?',
    Slosh = '\\',
  };

  ModifierT::Value value;

  Token::Feed Lex(Lexer *lexer, ModifierT *out);
};

#endif  // ANALYER_TOKEN_HPP
