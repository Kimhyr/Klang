#ifndef KPLC_UTILITIES_FLAG_CPP
#define KPLC_UTILITIES_FLAG_CPP

#include "../Definitions.cpp"

template<typename Bit_T>
class Flag {
public:
    Flag()
        : bits(0) {
    }

    Void Set();

private:
    Bit_T bits;
};

using Flag8 = Flag<Bit8>;
using Flag16 = Flag<Bit16>;
using Flag32 = Flag<Bit32>;
using Flag64 = Flag<Bit64>;


#endif // KPLC_UTILITIES_FLAG_CPP
