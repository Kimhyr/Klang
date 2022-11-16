#include "Lexer.hpp"

#include "../Utils/Char.hpp"
#include <iostream>

Lexer::Lexer(ErrorBuffer *errBuf, const Char8 *sourcePath, const Char8 *source)
  : errBuf(errBuf)
  , sourcePath(sourcePath)
  , index(-1)
  , source(source)
  , peek(source[0])
  , point({1, 1}) {
}

Void Lexer::Destroy() {
  this->buffer.Destroy();
}

Lexer::Flag Lexer::Lex(Token *out) {
  this->flags = 0;
  while (Char::IsWhitespace(this->peek)) {
    this->Advance();
  }
  out->start = this->point;
  if (Char::IsAlphabetic(this->peek)) {
    do {
      this->buffer.Put(this->peek);
      this->Advance();
    } while (Char::IsNumeric(this->peek) || Char::IsAlphabetic(this->peek) || this->peek == '_');
    if (this->buffer == "procedure") {
      out->value.Keyword = KeywordT::Procedure;
    } else if (this->buffer == "datum") {
      out->value.Keyword = KeywordT::Datum;
    } else if (this->buffer == "return") {
      out->value.Keyword = KeywordT::Return;
    } else {
      out->kind = Token::Kind::Identifier;
      out->value.Identifier = this->buffer.Flush();
      goto END;
    }
    out->kind = Token::Kind::Keyword;
  } else if (Char::IsNumeric(this->peek)) {
    out->kind = Token::Kind::Literal;
    do {
      if (this->peek != '_') {
        this->buffer.Put(this->peek);
      }
      this->Advance();
      if (this->peek == '.') {
        if (out->value.Literal.kind == LiteralT::Kind::Float) {
          this->errBuf->Put(Error(
            Error::Severity::Critical,
            "Float literal token has too many dots."
          ));
          this->flags |= Lexer::F::Err;
          break;
        }
      }
    } while (Char::IsNumeric(this->peek) || this->peek == '_' || this->peek == '.');
    out->value.Literal.value = this->buffer.Flush();
  } else {
    switch (this->peek) {
    case ':':
      switch (this->Peek(2)) {
      case ':':
        out->kind = Token::Kind::Oper;
        out->value.Oper = OperT::DColon;
        goto DOUBLE;
      default:
        break;
      }
    case '(':
    case ')':
    case '{':
    case '}':
    case ',':
    case ';':
      out->kind = Token::Kind::Punctuator;
      out->value.Punctuator = (PunctuatorT)this->peek;
      goto SINGLE;
    case '-':
      switch (this->Peek(2)) {
      case '>':
        out->kind = Token::Kind::Oper;
        out->value.Oper = OperT::RArrow;
        goto DOUBLE;
      default:
        break;
      }
    case '=':
    case '+':
      out->kind = Token::Kind::Oper;
      out->value.Oper = (OperT)this->peek;
      goto SINGLE;
    case '\\':
      switch (this->Peek(2)) {
      case '\\':
        out->kind = Token::Kind::None;
        do {
          this->Advance();
          if (this->peek == '\0') {
            this->flags |= Lexer::F::EoF;
            goto END;
          }
        } while (this->peek != '\n');
        this->flags |= Lexer::F::Continue;
        goto END;
      default:
        break;
      }
    case '@':
    case '?':
      out->kind = Token::Kind::Modifier;
      out->value.Modifier = (ModifierT)this->peek;
      goto SINGLE;
    default:
      out->kind = Token::Kind::None;
      this->flags |= Lexer::F::Err;
      goto SINGLE;
      break;
    }
  DOUBLE:
    this->Advance();
  SINGLE:
    this->Advance();
  }
END:
  out->end = this->point;
  --out->end.column;
  if (this->peek == '\0') {
    this->flags |= Lexer::F::EoF;
  }
  return this->flags;
}

Void Lexer::Advance() {
  ++this->index;
  if (this->peek == '\n') {
    ++this->point.row;
    this->point.column = 0;
  }
  ++this->point.column;
  this->peek = this->Peek();
}
