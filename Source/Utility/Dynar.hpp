#ifndef COMPILER_UTILITY_DYNAR_HPP
#define COMPILER_UTILITY_DYNAR_HPP

#include "../Definitions.hpp"

namespace Utility {
    template<typename DataT>
    class Dynar {
    public: // Constants
        static constexpr const UInt64 InitialSpace = 8;

    public: // Constructors and destructors
        explicit
        Dynar(UInt64 space = Dynar::InitialSpace);

        inline
        Void Destroy();

        inline
        DataT *Flush();

    public: // Procedures
        Void Put(DataT value);

        inline
        Void Expand();

    private: // Properties
        UInt64 space;
        UInt64 size;
        DataT data;

    private:
        Void Realloc();
    };
} // Utility

#endif // COMPILER_UTILITY_DYNAR_HPP
