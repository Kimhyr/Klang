#ifndef KC_UTILITIES_BUFFER_H
#define KC_UTILITIES_BUFFER_H

#include "../Include.H"
#include <sys/wait.h>

namespace U {
    template<typename Type_T, Size Size_V>
    class Buffer {
        Size index;
        Type_T *data;

    public:
        Bool Put(Type_T value);
        Type_T *Flush();

    public:
        constexpr
        Size GetIndex()
        const {
            return $ index;
        }

        constexpr
        const Type_T *GetData()
        const {
            return $ data;
        }
    };
} // U

#endif // KC_UTILITIES_BUFFER_H
