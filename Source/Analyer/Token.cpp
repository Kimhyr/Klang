#include "Token.hpp"

#include "../Utils/Char.hpp"

Token::Flag IdentifierT::Lex(Lexer *lexer) {
  UInt8 flags = 0;
  do {
    lexer->buffer.Put(lexer->peek);
    lexer->Advance();
  } while (Char::IsAlphabetic(lexer->peek) || Char::IsNumeric(lexer->peek) ||
           lexer->peek == '_');
  if (lexer->peek == '\0') {
    flags |= static_cast<UInt8>(Token::Flag::EoF);
  }
  this->identifier = lexer->buffer.Flush();
  return static_cast<Token::Flag>(flags);
}

// TODO
Token::Flag LiteralT::Lex(Lexer *lexer) {
  UInt8 flags = 0;
  switch (this->kind) {
  case LiteralT::Kind::Void:
    break;
  case LiteralT::Kind::Integer:
    do {
      lexer->buffer.Put(lexer->peek);
      lexer->Advance();
    } while (Char::IsNumeric(lexer->peek) || lexer->peek == '_');
    if (lexer->peek == '.') {
      if (lexer->peek == '\0') {
        flags |= static_cast<UInt8>(Token::Flag::EoF);
      }
      goto END;
    }
    this->kind = LiteralT::Kind::Float;
  case LiteralT::Kind::Float:
    do {
      lexer->buffer.Put(lexer->peek);
      lexer->Advance();
    } while (Char::IsNumeric(lexer->peek) || lexer->peek == '_');
    if (lexer->peek == '.') {
      flags |= static_cast<UInt8>(Token::Flag::Error);
      lexer->errBuf->Put(Error(
          Error::Severity::Critical,
          "This float literal token has too many dots."
      ));
    }
    if (lexer->peek == '\0') {
      flags |= static_cast<UInt8>(Token::Flag::EoF);
    }
    goto END;
  case LiteralT::Kind::Character:
    break;
  case LiteralT::Kind::String:
    break;
  }
END:
  return static_cast<Token::Flag>(flags);
}

Token::Flag KeywordT::Lex(Lexer *lexer) {
  UInt8 flags = 0;
  Char8 *str = &lexer->buffer.buffer[lexer->index - 1];
  if (lexer->peek == '\0') {
    flags |= static_cast<UInt8>(Token::Flag::EoF);
  }
  if (String::Compare(str, "procedure")) {
    this->value = KeywordT::Value::Procedure;
  } else if (String::Compare(str, "datum")) {
    this->value = KeywordT::Value::Datum;
  } else if (String::Compare(str, "return")) {
    this->value = KeywordT::Value::Return;
  } else {
    flags |= static_cast<UInt8>(Token::Flag::Switch);
  }
  return static_cast<Token::Flag>(flags);
}

Token::Flag OperT::Lex(Lexer *lexer) {
  UInt8 flags = 0;
  if (lexer->peek == '\0') {
    flags |= static_cast<UInt8>(Token::Flag::EoF);
  }
  switch (lexer->peek) {
  case '\0':
    flags |= static_cast<UInt8>(Token::Flag::EoF);
  default:
    break;
  }

  return static_cast<Token::Flag>(flags);
}

Token::Flag PunctuatorT::Lex(Lexer *lexer) {
  UInt8 flags = 0;
  if (lexer->peek == '\0') {
    flags |= static_cast<UInt8>(Token::Flag::EoF);
  }
  return static_cast<Token::Flag>(flags);
}

Token::Flag ModifierT::Lex(Lexer *lexer) {
  UInt8 flags = 0;
  if (lexer->peek == '\0') {
    flags |= static_cast<UInt8>(Token::Flag::EoF);
  }
  return static_cast<Token::Flag>(flags);
}
