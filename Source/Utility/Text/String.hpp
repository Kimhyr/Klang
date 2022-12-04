#ifndef KPLC_UTILITY_TEXT_TEXT_HPP
#define KPLC_UTILITY_TEXT_TEXT_HPP

#include "../Collections/Dynar.hpp"
#include "../../Definitions.hpp"

namespace Utility::Text {
    class String : public Collections::Dynar<Text8> {
    public:
        static
        Bool Compare(const Text8 *first, const Text8 *second);

        template<typename IntegerT>
        static
        IntegerT ConvertToInteger(const Text8 *string, Int32 base = 10);

        template<typename FloatT>
        static
        FloatT ConvertToFloat(const Text8 *string);
    };
} // Debugger

#endif // KPLC_UTILITY_TEXT_TEXT_HPP
