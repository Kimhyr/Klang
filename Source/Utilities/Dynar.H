#ifndef KC_UTILITIES_DYNAR_H
#define KC_UTILITIES_DYNAR_H

#include "../Include.H"

namespace U {
    template<typename Data_T>
    class Dynar {
        Size space;
        Size size;
        Data_T *data;

    public:
        static constexpr
        const Size INITIAL_SPACE = 8;

    public:
        explicit
        Dynar(Size space = Dynar::INITIAL_SPACE)
            : space(space),
              size(0),
              data(new Data_T[space]) {}

        Void Destroy();

        Data_T *Flush();

    public:
        Void Put(Data_T value);

    public:
        constexpr
        Size GetSpace()
        const { return $ space; }

        constexpr
        Size GetSize()
        const { return $ size; }

        constexpr
        const Data_T *GetData()
        const { return $ data; }
    };
} // U

#endif // KC_UTILITIES_DYNAR_H
