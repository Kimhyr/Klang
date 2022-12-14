#include "Dynar.H"

#include "Memory.H"

template<typename Data_T>
Void Dynar<Data_T>::Destroy() {
    delete[] $ data;
}

template<typename Data_T>
Data_T *Dynar<Data_T>::Flush() {
    $ Reallocate($ size);
    return $ data;
}

template<typename Data_T>
Void Dynar<Data_T>::Put(Data_T value) {
    ++$ size;
    if ($ size > $ space)
        $ data = Memory::Reallocate($ data, $ space *= 2);
    $ data[$ size - 1] = value;
}
