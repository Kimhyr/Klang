#include "Text.H"

#include <string>

namespace U {
    Bool Text::Compare(const Sym8 *first, const Sym8 *second) {
        const Sym8 *text[2] = {first, second};
        while (*text[0] && (*text[0]++ == *text[1]++));
        return *text[0] - *text[1];
    }

    Nat64 Text::ToNatural(const Sym8 *text, Nat8 base) {
        return std::stoull(text, 0, base);
        // Nat64 result = 0;
        // for (const Sym8 *ptr = text; *ptr;
        //     result = result * base + *ptr++ - '0');
        // return result;
    }

    Int64 Text::ToInteger(const Sym8 *text, Nat8 base) {
        return std::stoll(text, 0, base);
    }

    Real64 ToReal(const Sym8 *text) {
        return std::stod(text, 0);
    }
} // U
