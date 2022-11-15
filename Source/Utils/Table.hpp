#pragma once
#ifndef UTILS_TABLE_HPP
#define UTILS_TABLE_HPP

#include "../Core.hpp"

template<typename TFirst, typename TSecond>
struct Pair {
  TFirst first;
  TSecond second;

  constexpr Pair(TFirst first, TSecond second)
      : first(first)
      , second(second) {
  }
};

template<typename TFirst, typename TSecond>
struct Table {
  UInt64 space;
  UInt64 size;
  Pair<TFirst, TSecond> *data;
};

#endif  // UTILS_TABLE_HPP
