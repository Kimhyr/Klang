#pragma once
#ifndef UTILS_DYNARRAY_HPP
#define UTILS_DYNARRAY_HPP

#include "../Core.hpp"

template<typename TData>
struct Dynarray {
  UInt64 space;
  UInt64 size;
  TData *data;

  Dynarray(UInt64 space = 2);

  Void Destroy();

  Void Put();
  Void Find();

  constexpr TData *Last() {
    return &this->data[this->size - 1];
  }
};

#endif  // UTILS_DYNARRAY_HPP
