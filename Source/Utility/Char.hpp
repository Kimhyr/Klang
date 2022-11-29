#ifndef KPLC_UTILITY_CHAR_HPP
#define KPLC_UTILITY_CHAR_HPP

#include "../Definitions.hpp"

namespace Utility {
    struct Char {
        static inline constexpr
        Bool IsWhitespace(Char8 in) { return (in == ' ') || (in >= '\t' && in <= '\r') }

        static inline constexpr
        Bool IsAlphabetic(Char8 in) { return (in >= 'A' && in <= 'Z') || (in >= 'a' && in <= 'z'); }

        static inline constexpr
        Bool IsNumeric(Char8 in) { return in >= '0' && in <= '9'; };
    };
} // Utility

#endif //KPLC_UTILITY_CHAR_HPP
