#ifndef KPLC_UTILITIES_FLAG_CPP
#define KPLC_UTILITIES_FLAG_CPP

#include "../Definitions.cpp"

template<typename Bit_T, typename Type_T>
class Flag {
    Bit_T bits;

public:
    Flag()
        : bits(0)
    {}

    Bool Check(Type_T check) {
        return $ (bits | ~((Bit_T)check)) & (Bit_T)check;
    }

    Void Set(Type_T check) {
        $ bits |= (Bit_T)check;
    }
};

template<typename Type_T>
using Flag8 = Flag<Bit8, Type_T>;

template<typename Type_T>
using Flag16 = Flag<Bit16, Type_T>;

template<typename Type_T>
using Flag32 = Flag<Bit32, Type_T>;

template<typename Type_T>
using Flag64 = Flag<Bit64, Type_T>;

#endif // KPLC_UTILITIES_FLAG_CPP
