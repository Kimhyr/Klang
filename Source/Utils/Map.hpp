#pragma once
#ifndef UTILS_MAP_HPP
#define UTILS_MAP_HPP

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

template<typename TKey, typename TValue>
struct Map {
  UInt64 space;
  UInt64 size;
  Pair<TKey, TValue> *data;

  Map();
  Map(Pair<TKey, TValue> *data, UInt64 size);
  Void Put(Pair<TKey, TValue> in);
  TValue *Get(const TKey *key);
};

#endif  // UTILS_MAP_HPP
