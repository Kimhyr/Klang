#include "Memory.hpp"

namespace Utility::System {
    template<typename DataT>
    DataT *Memory::Reallocate(
        Nat64 dataSize, DataT *data,
        Nat64 destinationSize
    ) {
        auto mlock = new DataT[destinationSize];
        for (Nat64 i = 0; i < dataSize; ++i) {
            mlock[i] = data[i];
        }
        delete[] data;
        return mlock;
    }
} // System
