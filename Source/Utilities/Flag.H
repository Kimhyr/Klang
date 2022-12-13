#ifndef KC_UTILITIES_FLAG_H
#define KC_UTILITIES_FLAG_H

#include "../Include.H"

namespace U {
    template<typename Bit_T, typename Type_T>
    class Flag {
        Bit_T bits;

    public:
        Flag()
            : bits(0) {}

        constexpr
        Bool Check(Type_T check)
        const { return ($ bits | ~((Bit_T)check)) & (Bit_T)check; }

        constexpr
        Void Set(Type_T set) {
            $ bits |= (Bit_T)set;
        }
    };

    template<typename Type_T>
    using Flag8 = Flag<Bit8, Type_T>;
} // U

#endif // KC_UTILITIES_FLAG_H
