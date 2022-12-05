#ifndef KPLC_UTILITIES_MEMORY_CPP
#define KPLC_UTILITIES_MEMORY_CPP

#include "../Definitions.cpp"

namespace U {
    class Memory {
    public:
        template<typename Data_T>
        static
        Data_T *Reallocate(
            Nat64 dataSize, Data_T *data,
            Nat64 newSize
        ) noexcept {
            auto mlock = new Data_T[newSize];
            for (
                Nat64 i = 0; i < dataSize; ++i
                ) {
                mlock[i] = data[i];
            }
            delete[] data;
            return mlock;
        }
    };
} // U

#endif // KPLC_UTILITIES_MEMORY_CPP
