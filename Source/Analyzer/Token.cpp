#include "Token.hpp"

#include <sstream>

const Char8 *T::Literal::ToStr() {
  std::stringstream ss;
  ss << "LiteralT{flags=" << (UInt8)this->flags;
  switch (this->kind) {
  case T::Literal::Kind::Integer:
    ss << ",Integer,";
    break;
  case T::Literal::Kind::Float:
    ss << ",Float,";
    break;
  case T::Literal::Kind::Character:
    ss << ",Character,";
    break;
  case T::Literal::Kind::String:
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
     << ", end=" << this->end.ToStr();  // << ",kind=" << this->KindToStr()
                                        // << ",value=";
  ss << "}";
  return ss.str().c_str();
}
