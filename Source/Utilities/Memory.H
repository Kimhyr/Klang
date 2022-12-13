#ifndef KC_UTILITIES_MEMORY_H
#define KC_UTILITIES_MEMORY_H

#include "../Include.H"

namespace U {
    class Memory {
    public:
        template<typename Data_T>
        static
        Data_T *Reallocate(Size dataSize, Data_T *data,
                           Size newSize);
    };
} // U

#endif // KC_UTILITIES_MEMORY_H
