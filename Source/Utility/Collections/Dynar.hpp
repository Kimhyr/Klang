#ifndef KPLC_COLLECTIONS_DYNAR_HPP
#define KPLC_COLLECTIONS_DYNAR_HPP

#include "../../Definitions.hpp"

namespace Utility::Collections {
    template<typename DataT>
    class Dynar {
    public:
        static constexpr const UInt64 InitialSpace = 8;

    public:
        explicit
        Dynar(UInt64 space = Dynar::InitialSpace);

        Void Destroy();

        DataT *Flush();

    public:
        [[nodiscard]]
        constexpr
        UInt64 GetSpace()
        const noexcept { return this->space; }

        [[nodiscard]]
        constexpr
        UInt64 GetSize()
        const noexcept { return this->size; }

        [[nodiscard]]
        constexpr
        const DataT *GetData()
        const noexcept { return this->data; }

    public:
        Void Put(DataT value);

    private:
        UInt64 space;
        UInt64 size;
        DataT *data;

    private:
        inline
        Void Reallocate(UInt64 newSpace);
    };
} // Utility::Collection

#endif // KPLC_COLLECTIONS_DYNAR_HPP
