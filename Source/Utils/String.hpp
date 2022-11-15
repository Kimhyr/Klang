#pragma once
#ifndef UTILS_STRING_HPP
#define UTILS_STRING_HPP

#include "../Core.hpp"

struct String {
  UInt64 space;
  UInt64 size;
  Char8 *buffer;

  String(UInt64 space = 2);
  Void Destroy();
  Void Put(Char8 value);
  Bool operator==(const Char8 *comparee);
  Bool operator==(const String *comparee);
  static Char8 Compare(const Char8 *str, const Char8 *comparee);
  Void Realloc();
  Char8 *Flush();
  Char8 *ToStr();
};

#endif  // UTILS_STRING_HPP
