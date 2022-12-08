#ifndef KPLC_UTILITIES_DYNAR_CPP
#define KPLC_UTILITIES_DYNAR_CPP

#include "../Definitions.cpp"
#include "Memory.cpp"

namespace U {
    template<typename Data_T>
    class Dynar {
        Nat64 space;
        Nat64 size;
        Data_T *data;

    public:
        static constexpr
        const Nat64
        INITIAL_SPACE = 8;

    public:
        explicit
        Dynar(Nat64 space = Dynar::INITIAL_SPACE)
            : space(space),
              size(0),
              data(new Data_T[space])
        {}

        inline
        Void Destroy()
        { delete[] $ data; }

        inline
        Data_T *Flush()
        {
            $ Reallocate($ size);
            return $ data;
        }

    public:
        inline
        Void Put(Data_T value) {
            ++$ size;
            if ($ size > $ space)
                $ Reallocate($ space * 2);
            $ data[$ size - 1] = value;
        }

    public:
        [[nodiscard]]
        constexpr
        Nat64 Space()
        const noexcept
        { return $ space; }

        [[nodiscard]]
        constexpr
        Nat64 Size()
        const noexcept
        { return $ size; }

        [[nodiscard]]
        constexpr
        const Data_T * Data()
        const noexcept
        { return $ data; }

    private:
        inline
        Void Reallocate(Nat64 newSpace) {
            $ space = newSpace;
            $ data = U::Memory::Reallocate($ size, $ data,
                                           $ space);
        }
    };
} // U

#endif // KPLC_UTILITIES_DYNAR_CPP
