#ifndef KPLC_TEXT_TEXT_HPP
#define KPLC_TEXT_TEXT_HPP

#include "../Collections/Dynar.hpp"
#include "../../Definitions.hpp"

namespace Utility::Text {
    class String : public Collections::Dynar<Char8> {
    public:
        static
        Bool Compare(const Char8 *first, const Char8 *second);

        template<typename IntegerT>
        static
        IntegerT ConvertToInteger(const Char8 *string, Int32 base = 10);

        template<typename FloatT>
        static
        FloatT ConvertToFloat(const Char8 *string);
    };

} // Debugger

#endif // KPLC_TEXT_TEXT_HPP
