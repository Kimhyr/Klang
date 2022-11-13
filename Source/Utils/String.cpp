#include "String.hpp"

#include <string>

String::String(UInt64 space) {
  this->space = space;
  this->size = 0;
  this->buffer = new Char8[space];
  this->buffer[0] = '\0';
}

Void String::Destroy() {
  delete[] this->buffer;
}

Bool String::operator==(const Char8 *comparee) {
  return strcmp(this->buffer, comparee) == 0;
}

Bool String::operator==(const String *comparee) {
  return strcmp(this->buffer, comparee->buffer) == 0;
}

Void String::Realloc() {
  Char8 *mlock = new Char8[this->space];
  for (UInt64 i = 0; i < this->size + 1; ++i) {
    mlock[i] = this->buffer[i];
  }
  delete[] this->buffer;
  this->buffer = mlock;
}

Void String::Put(Char8 chr) {
  ++this->size;
  if (this->size >= this->space) {
    this->space *= 2;
    this->Realloc();
  }
  this->buffer[this->size - 1] = chr;
  this->buffer[this->size] = '\0';
}

Char8 *String::ToStr() {
  Char8 *str = new Char8[this->size + 1];
  for (UInt64 i = 0; i < this->size + 1; ++i) {
    str[i] = this->buffer[i];
  }
  return str;
}
