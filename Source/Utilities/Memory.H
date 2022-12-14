#ifndef KC_UTILITIES_MEMORY_H
#define KC_UTILITIES_MEMORY_H

#include "../Include.H"

class Memory {
public:
    template<typename Data_T>
    static
    Data_T *Reallocate(Size dataSize, Data_T *data,
                        Size newSize);
};

#endif // KC_UTILITIES_MEMORY_H
