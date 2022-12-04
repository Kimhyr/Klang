#ifndef KPLC_UTILITY_SYSTEM_MEMORY_HPP
#define KPLC_UTILITY_SYSTEM_MEMORY_HPP

#include "../../Definitions.hpp"

namespace Utility::System {
    class Memory {
    public:
        template<typename DataT>
        static
        DataT *Reallocate(
            Nat64 dataSize, DataT *data,
            Nat64 destinationSize
        );
    };
} // System

#endif // KPLC_UTILITY_SYSTEM_MEMORY_HPP
