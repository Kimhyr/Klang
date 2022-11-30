#include "String.hpp"

#include <string>

namespace Text {
    Bool String::Compare(const Char8 *first, const Char8 *second) {
        const Char8 *c_first = first;
        const Char8 *c_second = second;
        while (*c_first && (*c_first == *c_second)) {
            ++c_first;
            ++c_second;
        }
        return *c_first - *c_second;
    }

    template<>
    UInt64 String::ConvertToInteger<UInt64>(const Char8 *string, Int32 base) {
        return std::stoull(string, 0, base);
    }

    template<>
    Float64 String::ConvertToFloat<Float64>(const Char8 *string) {
        return std::stod(string, 0);
    }

} // Debugger