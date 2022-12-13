#include "Memory.H"

namespace U {
    template<typename Data_T>
    static
    Data_T *Reallocate(Size dataSize, Data_T *data,
                       Size newSize) {
        auto mlock = new Data_T[newSize];
        for (Size i = 0; i < dataSize; ++i)
            mlock = data[i];
        delete[] data;
        return mlock;
    }
} // U
