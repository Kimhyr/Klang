#ifndef KC_UTILITIES_BUFFER_H
#define KC_UTILITIES_BUFFER_H

#include "../Include.H"

template<typename Type_T, Size Size_V>
class Buffer {
    Size size;
    Type_T *data;

public:
    Bool Put(Type_T value);
    Type_T *Flush();

public:
    constexpr
    Size GetSize()
    const {
        return $ size;
    }

    constexpr
    const Type_T *GetData()
    const {
        return $ data;
    }
};

#endif // KC_UTILITIES_BUFFER_H
