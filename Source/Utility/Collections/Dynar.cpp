#include "Dynar.hpp"

#include "../System/Memory.hpp"

namespace Utility::Collections {
    using namespace Utility::System;

    template<typename Data_T>
    Dynar<Data_T>::Dynar(Nat64 space)
        : space(space),
          size(0),
          data(new Data_T[space]) {
    }

    template<typename Data_T>
    Void Dynar<Data_T>::Destroy() {
        delete[] this->data;
    }

    template<typename Data_T>
    Data_T *Dynar<Data_T>::Flush() {
        this->Reallocate(this->size);
        return this->data;
    }

    template<typename Data_T>
    Void Dynar<Data_T>::Put(Data_T value) {
        this->size++;
        if (this->size > this->space) {
            this->Reallocate(this->space * 2);
        }
        this->data[this->size - 1] = value;
    }

    template<typename Data_T>
    Void Dynar<Data_T>::Reallocate(Nat64 newSpace) {
        this->space = newSpace;
        this->data = Memory::Reallocate(
            this->size, this->data,
            this->space
        );
    }
} // Debugger
