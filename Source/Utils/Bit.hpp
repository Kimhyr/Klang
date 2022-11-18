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
        *bits = 0;
    }
            
    static constexpr Bool Check(UInt64 bits, UInt8 nth) {
        return bits & (1 << (nth - 1));
    }

    template<typename TFlag, typename TCheck>
    static constexpr Bool Check(TFlag flags, TCheck check) {
        return flags & (1 << (check - 1));
    } 

    template<typename TFlags>
    static constexpr Void Set(TFlags *flags, TFlags set) {
        *flags |= (UInt64)set;
    }
};

#endif  // UTILS_BIT_HPP
