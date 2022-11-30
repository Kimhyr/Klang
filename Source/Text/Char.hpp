#ifndef KPLC_TEXT_CHAR_HPP
#define KPLC_TEXT_CHAR_HPP

#include "../Definitions.hpp"

namespace Text {
    struct Char {
        static constexpr
        Bool IsWhitespace(Char8 in) { return (in == ' ') || (in >= '\t' && in <= '\r'); }

        static constexpr
        Bool IsAlphabetic(Char8 in) { return (in >= 'A' && in <= 'Z') || (in >= 'a' && in <= 'z'); }

        static constexpr
        Bool IsNumeric(Char8 in) { return in >= '0' && in <= '9'; };
    };
} // Debugger

#endif // KPLC_TEXT_CHAR_HPP
