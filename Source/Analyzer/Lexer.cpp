#include "Lexer.hpp"

#include <iostream>

#include "../Utils/Bit.hpp"
#include "../Utils/Char.hpp"

Lexer::Lexer(ErrorBuffer *errBuf, const Char8 *source)
    : errBuf(errBuf)
    , index(-1)
    , source(source)
    , peek(source[0])
    , point({1, 1}) {
}

Void Lexer::Destroy() {
  this->buffer.Destroy();
}

Lexer::Flag Lexer::Lex(Token *out) {
  Bit::Clear(&this->flags);
  while (Char::IsWhitespace(this->peek)) {
    this->Advance();
  }
  out->start = this->point;
  if (Char::IsAlphabetic(this->peek)) {
    do {
      this->buffer.Put(this->peek);
      this->Advance();
    } while (Char::IsNumeric(this->peek) || Char::IsAlphabetic(this->peek) ||
             this->peek == '_');
    if (this->buffer == "procedure") {
      out->value.Symbol = T::Symbol::Procedure;
    } else if (this->buffer == "datum") {
      out->value.Symbol = T::Symbol::Datum;
    } else if (this->buffer == "return") {
      out->value.Symbol = T::Symbol::Return;
    } else {
      out->kind = Token::Kind::Identifier;
      out->value.Identifier = this->buffer.Flush();
      goto END;
    }
    out->kind = Token::Kind::Symbol;
  } else if (Char::IsNumeric(this->peek)) {
    out->kind = Token::Kind::Literal;
    do {
      if (this->peek != '_') {
        this->buffer.Put(this->peek);
      }
      this->Advance();
      if (this->peek == '.') {
        if (out->value.Literal.kind == T::Literal::Kind::Float) {
          this->errBuf->Put(Error(
              Error::Severity::Critical,
              "Float literal token has too many dots."
          ));
          Bit::Set(&this->flags, Lexer::Flag::Error);
          break;
        }
      }
    } while (Char::IsNumeric(this->peek) || this->peek == '_' ||
             this->peek == '.');
    out->value.Literal.value = this->buffer.Flush();
  } else {
    out->kind = Token::Kind::Symbol;
    switch (this->peek) {
    case '\\':
      switch (this->Peek(2)) {
      case '\\':
        out->kind = Token::Kind::None;
        do {
          this->Advance();
          if (this->peek == '\0') {
            Bit::Set(&this->flags, Lexer::Flag::EoF);
            goto END;
          }
        } while (this->peek != '\n');
        Bit::Set(&this->flags, Lexer::Flag::Continue);
        goto END;
      default:
        break;
      }
    case ':':
      switch (this->Peek(2)) {
      case ':':
        out->value.Symbol = T::Symbol::DColon;
        goto DOUBLE;
      default:
        break;
      }
    case '-':
      switch (this->Peek(2)) {
      case '>':
        out->kind = Token::Kind::Symbol;
        out->value.Symbol = T::Symbol::RArrow;
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
    case '=':
    case '+':
    case '@':
    case '?':
      out->value.Symbol = (T::Symbol)this->peek;
      goto SINGLE;
    default:
      out->kind = Token::Kind::None;
      Bit::Set(&this->flags, Lexer::Flag::Error);
      goto SINGLE;
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
    Bit::Set(&this->flags, Lexer::Flag::EoF);
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
