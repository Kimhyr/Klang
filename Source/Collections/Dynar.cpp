#include "Dynar.hpp"

#include "../System/Memory.hpp"

namespace Collections {
    using namespace System;

    template<typename DataT>
    Dynar<DataT>::Dynar(UInt64 space)
            : space(space),
              size(0),
              data(new DataT[space]) {
    }

    template<typename DataT>
    Void Dynar<DataT>::Destroy() {
        delete[] this->data;
    }

    template<typename DataT>
    DataT *Dynar<DataT>::Flush() {
        this->Reallocate(this->size);
        return this->data;
    }

    template<typename DataT>
    Void Dynar<DataT>::Put(DataT value) {
        this->size++;
        if (this->size > this->space) {
            this->Reallocate(this->space * 2);
        }
        this->data[this->size - 1] = value;
    }

    template<typename DataT>
    Void Dynar<DataT>::Reallocate(UInt64 newSpace) {
        this->space = newSpace;
        this->data = Memory::Reallocate(
                this->size, this->data,
                this->space
        );
    }
} // Debugger
