#include "Token.hpp"

#include <sstream>

const Char8 *LiteralT::ToStr() {
  std::stringstream ss;
  ss << "LiteralT{flags=" << (UInt8)this->flags;
  switch (this->kind) {
  case LiteralT::Kind::Integer:
    ss << ",Integer,";
    break;
  case LiteralT::Kind::Float:
    ss << ",Float,";
    break;
  case LiteralT::Kind::Character:
    ss << ",Character,";
    break;
  case LiteralT::Kind::String:
    ss << ",String,";
    break;
  }
  ss << "value=" << this->value << "}";
  return ss.str().c_str();
}

const Char8 *Token::Point::ToStr() {
  std::stringstream ss;
  ss << "Point{row=" << this->row << ",column=" << this->column << "}";
  return ss.str().c_str();
}

const Char8 *Token::ToStr() {
  std::stringstream ss;
  ss << "Token{start=" << this->start.ToStr()
     << ", end=" << this->end.ToStr() << ",kind=" << this->KindToStr()
     << ",value=";
  switch (this->kind) {
  case Token::Kind::None:
    ss << "None";
  case Token::Kind::Identifier:
    ss << this->value.Identifier;
  case Token::Kind::Keyword:
    ss << this->KeywordToStr();
  case Token::Kind::Literal:
    ss << this->value.Literal.ToStr();
  case Token::Kind::Punctuator:
    ss << this->PunctuatorToStr();
  case Token::Kind::Oper:
    ss << this->OperToStr();
  case Token::Kind::Modifier:
    ss << this->ModifierToStr();
  }
  ss << "}";
  return ss.str().c_str();
}
