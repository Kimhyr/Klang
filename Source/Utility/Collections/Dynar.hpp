#ifndef KPLC_UTILITY_COLLECTIONS_DYNAR_HPP
#define KPLC_UTILITY_COLLECTIONS_DYNAR_HPP

#include "../../Definitions.hpp"

namespace Utility::Collections {
    template<typename Data_T>
    class Dynar {
    public:
        static constexpr
        const Nat64 INITIAL_SPACE = 8;

    public:
        explicit
        Dynar(Nat64 space = Dynar::INITIAL_SPACE);

        Void Destroy();

        Data_T *Flush();

    public:
        [[nodiscard]]
        constexpr
        Nat64 GetSpace()
        const noexcept { return this->space; }

        [[nodiscard]]
        constexpr
        Nat64 GetSize()
        const noexcept { return this->size; }

        [[nodiscard]]
        constexpr
        const Data_T *GetData()
        const noexcept { return this->data; }

    public:
        Void Put(Data_T value);

    private:
        Nat64 space;
        Nat64 size;
        Data_T *data;

    private:
        inline
        Void Reallocate(Nat64 newSpace);
    };
} // Utility::Collection

#endif // KPLC_UTILITY_COLLECTIONS_DYNAR_HPP
