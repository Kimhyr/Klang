#ifndef KPLC_SYSTEM_MEMORY_HPP
#define KPLC_SYSTEM_MEMORY_HPP

#include "../../Definitions.hpp"

namespace Utility::System {
    class Memory {
    public:
        template<typename DataT>
        static
        DataT *Reallocate(
                UInt64 dataSize, DataT *data,
                UInt64 destinationSize
        );
    };
} // System

#endif // KPLC_SYSTEM_MEMORY_HPP
