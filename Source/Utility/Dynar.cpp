#include "Dynar.hpp"

namespace Utility {
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
        this->space = this->size;
        this->Realloc();
        return this->data;
    }

    template<typename DataT>
    Void Dynar<DataT>::Put(DataT value) {
        this->size++;
        if (this->size > this->space) {
            this->space *= 2;
            this->Realloc();
        }
        this->data[this->size - 1] = value;
    }

    template<typename DataT>
    Void Dynar<DataT>::Expand() {
        this->space *= 2;
        this->Realloc();
    }

    template<typename DataT>
    Void Dynar<DataT>::Realloc() {
        auto mlock = new DataT[this->space];
        for (UInt64 i = 0; i < this->size; ++i) {
            mlock[i] = this->data[i];
        }
        delete[] this->data;
        this->data = mlock;
    }
} // Utility
