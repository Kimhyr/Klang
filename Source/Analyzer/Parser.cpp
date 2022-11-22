#include "Parser.hpp"

#include "../Utils/Bit.hpp"

Parser::Parser(ErrorBuffer *errBuf, const Char8 *source)
    : errBuf(errBuf)
    , lexer(errBuf, source) {
}

Void Parser::Destroy() {
  this->lexer.Destroy();
  this->stateBuffer.Destroy();
  this->declarations.Destroy();
}

template<>
Bool Parser::Parse(O::Identifier *out) {
  return false;
}

template<>
Bool Parser::Parse(O::Parameter *out) {
  return false;
}

template<>
Bool Parser::Parse(S::Procedure *out) {
  if (!this->Advance()) {
    // Error
  }

  this->declarations.Put(O::Declaration(out));
  if (!this->Parse<O::Identifier>(&this->declarations.Last()->identifier)) {
    // Error
  }

  if (!this->Advance()) {
    // Error
  }

  for (UInt8 i = 0; i < 3; ++i) {
    switch (this->token.kind) {
    case Token::Kind::Symbol:
      switch (this->token.value.Symbol) {
      case T::Symbol::OParen:
        if (!this->Parse(&out->parameter)) {
          // Error
        }
        break;
      case T::Symbol::RArrow:
        if (!this->Parse(&out->type)) {
          // Error.
        }
        break;
      case T::Symbol::OCurl:
        if (!this->Parse(&out->body)) {
          // Error
        }
        goto DONE;
      default:
        // Error
        break;
      }
      break;
    default:
      // Error
      break;
    }
  }

DONE:
  return true;
}

Bool Parser::Advance() {
  return false;
}
