#ifndef KC_UTILITIES_RESULT_H
#define KC_UTILITIES_RESULT_H

#include "../Include.H"

namespace U {
    template<typename Type_T>
    class Result {
    public:
        enum E : Int8 {
            FAILURE = -1,
            SUCCESS,
        };

    public:
        Result::E e;
        Type_T value;


    public:
        constexpr
        Type_T *Check() {
            switch ($ e) {
            case Result::FAILURE:
                return nil;
            case Result::SUCCESS:
                return &$ value;
            }
        }

        constexpr
        Void Set(Type_T value) {
            $ value = value;
        }
    };
} // U

#endif // KC_UTILITIES_RESULT_H
