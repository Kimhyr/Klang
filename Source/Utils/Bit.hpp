#pragma once
#ifndef UTILS_BIT_HPP
#define UTILS_BIT_HPP

#include "../Core.hpp"

using Bit8 = unsigned char;
using Bit16 = unsigned short int;
using Bit32 = unsigned int;
using Bit64 = unsigned long long int;

struct Bit {
    template<typename TBit>
    static constexpr Bool Bit_0(TBit bit) {
        return (bit | 0xfe) ^ 0xfe;
    }
    template<typename TBit>
    static constexpr Bool Bit_1(TBit bit) {
        return (bit | 0xfd) ^ 0xfd;
    }
    template<typename TBit>
    static constexpr Bool Bit_2(TBit bit) {
        return (bit | 0xfb) ^ 0xfb;
    }

};

#endif  // UTILS_BIT_HPP
