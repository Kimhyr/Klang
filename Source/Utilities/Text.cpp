#ifndef KPLC_UTILITIES_TEXT_CPP
#define KPLC_UTILITIES_TEXT_CPP

#include <string>

#include "../Definitions.cpp"

namespace U {
    class Text {
    public:
        static
        Bool Compare(const Text8 *first, const Text8 *second) {
            const Text8 *_first = first;
            const Text8 *_second = second;
            while (*_first && (*_first == *_second)) {
                ++_first;
                ++_second;
            }
            return *_first - *_second;
        }

        static inline
        Nat64 ConvertToNatural(const Text8 *string, Int32 base = 10) { return std::stoull(string, 0, base); }

        static inline
        Int64 ConvertToInteger(const Text8 *string, Int32 base = 10) { return std::stoll(string, 0, base); }

        static inline
        Real64 ConvertToReal(const Text8 *string) { return std::stod(string, 0); }

        static constexpr
        Bool IsWhitespace(Text8 text) { return (text == ' ') || (text >= '\t' && text <= '\r'); }

        static constexpr
        Bool IsAlphabetic(Text8 text) { return (text >= 'A' && text <= 'Z') || (text >= 'a' && text <= 'z'); }

        static constexpr
        Bool IsNumeric(Text8 text) { return text >= '0' && text <= '9'; };
    };
} // U

#endif // KPLC_UTILITIES_TEXT_CPP
