#pragma once
#ifndef UTILS_BIT_HPP
#define UTILS_BIT_HPP

#include "../Core.hpp"

using Bit8 = unsigned char;
using Bit16 = unsigned short int;
using Bit32 = unsigned int;
using Bit64 = unsigned long long int;

struct Bit {
  template<typename TBits>
  static constexpr Void Clear(TBits *bits) {
    Bit64 t_flags = (Bit64)bits;
    t_flags = 0;
    *bits = (TBits)t_flags;
  }

  static constexpr Bool Check(Bit64 bits, Bit8 nth) {
    return bits & (1 << (nth - 1));
  }

  template<typename TFlag, typename TCheck>
  static constexpr Bool Check(TFlag flags, TCheck check) {
    return (Bit64)flags & (1 << ((Bit64)check - 1));
  }

  template<typename TFlags, typename TSet>
  static constexpr Void Set(TFlags *flags, TSet set) {
    Bit64 t_flags = (Bit64)flags;
    t_flags |= (Bit64)set;
    *flags = (TFlags)t_flags;
  }
};

#endif  // UTILS_BIT_HPP
