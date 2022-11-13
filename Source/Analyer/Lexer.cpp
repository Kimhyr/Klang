#include "Lexer.hpp"

Void Lexer::Advance() {
  if (this->Peek() == '\n') {
    ++this->point.row;
    this->point.column = 0;
  }
  ++this->point.column;
  ++this->index;
}
