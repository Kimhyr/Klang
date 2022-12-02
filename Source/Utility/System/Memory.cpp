#include "Memory.hpp"

namespace Utility::System {
    template<typename DataT>
    DataT *Memory::Reallocate(
            UInt64 dataSize, DataT *data,
            UInt64 destinationSize
    ) {
        auto mlock = new DataT[destinationSize];
        for (UInt64 i = 0; i < dataSize; ++i) {
            mlock[i] = data[i];
        }
        delete[] data;
        return mlock;
    }
} // System
