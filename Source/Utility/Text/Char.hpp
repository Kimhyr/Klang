#ifndef KPLC_UTILITY_TEXT_CHAR_HPP
#define KPLC_UTILITY_TEXT_CHAR_HPP

#include "../../Definitions.hpp"

namespace Utility::Text {
    struct Char {
        static constexpr
        Bool IsWhitespace(Text8 in) { return (in == ' ') || (in >= '\t' && in <= '\r'); }

        static constexpr
        Bool IsAlphabetic(Text8 in) { return (in >= 'A' && in <= 'Z') || (in >= 'a' && in <= 'z'); }

        static constexpr
        Bool IsNumeric(Text8 in) { return in >= '0' && in <= '9'; };
    };
} // Debugger

#endif // KPLC_UTILITY_TEXT_CHAR_HPP
