#include "String.hpp"

namespace Text {
    Bool String::Compare(const Char8 *first, const Char8 *second) {
        Char8 *c_first = first;
        Char8 *c_second = second;
        while (*c_first && (*c_first == *c_second)) {
            ++cfirst;
            ++c_second;
        }
        return *c_first - *c_second;
    }
} // Debugger