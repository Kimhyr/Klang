#include "String.hpp"

#include <string>

namespace Utility::Text {
    Bool String::Compare(const Text8 *first, const Text8 *second) {
        const Text8 *c_first = first;
        const Text8 *c_second = second;
        while (*c_first && (*c_first == *c_second)) {
            ++c_first;
            ++c_second;
        }
        return *c_first - *c_second;
    }

    template<>
    Nat64 String::ConvertToInteger<Nat64>(const Text8 *string, Int32 base) {
        return std::stoull(string, 0, base);
    }

    template<>
    Float64 String::ConvertToFloat<Float64>(const Text8 *string) {
        return std::stod(string, 0);
    }

} // Debugger