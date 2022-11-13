#include "Lexer.hpp"

Void Lexer::Advance() {
  this->peek = this->Peek();
  if (this->peek == '\n') {
    ++this->point.row;
    this->point.column = 0;
  }
  ++this->point.column;
  ++this->index;
}
