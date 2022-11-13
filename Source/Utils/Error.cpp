#include "Error.hpp"

#include <iostream>

Void Error::Destroy() {
  delete[] this->message;
}

ErrorBuffer::ErrorBuffer(UInt64 space)
  : space(space), size(0), buffer(new Error[space]) {}

Void ErrorBuffer::Destroy() {
  while (this->size > 0) {
    this->buffer[this-> size - 1].Destroy();
    --this->size;
  }
  delete[] this->buffer;
}

Void ErrorBuffer::Put(Error error) {
  ++this->size;
  if (this->size > this->space) {
    Error *mlock = new Error[this->space];
    for (UInt64 i = 0; i < this->size; ++i) {
      mlock[i] = this->buffer[i];
    }
    delete[] this->buffer;
    this->buffer = mlock;
  }
  this->buffer[this->size - 1] = error;
}

Void ErrorBuffer::Flush() {
  while (this->size > 0) {
    Error *err = &this->buffer[this->size - 1];
    switch (err->severity) {
    case Error::Severity::Minor:
      std::cout << "Minor error: ";
    case Error::Severity::Major:
      std::cout << "Major error: ";
    case Error::Severity::Critical:
      std::cout << "Critical error: ";
    default:
      break;
    }
    std::cout << err->message << '\n';
    err->Destroy();
    --this->size;
  }
}
