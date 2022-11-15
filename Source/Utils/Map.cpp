#include "Map.hpp"

template<typename TKey, typename TValue>
Map<TKey, TValue>::Map()
    : space(2), size(0), data(new Pair<TKey, TValue>[2]) {
}

template<typename TKey, typename TValue>
Map<TKey, TValue>::Map(Pair<TKey, TValue> *data, UInt64 size)
    : data(data), size(size), space(size * 2) {
}

template<typename TKey, typename TValue>
Void Map<TKey, TValue>::Put(Pair<TKey, TValue> in) {
    ++this->size;
    if (this->size <= this->space) {
        this->data[this->size - 1] = in;
    }
    this->space *= 2;
    Pair<TKey, TValue> *mlock = new Pair<TKey, TValue>[this->space];
    for (UInt64 i = 0; i < this->size; ++i) {
        mlock[i] = this->data[i];
    }
    delete[] this->data;
    this->data = mlock;
}

template<typename TKey, typename TValue>
TValue *Map<TKey, TValue>::Get(const TKey *key) {
    for (UInt64 i = 0; i < this->size; ++i) {
        if (this->data[i].first == *key) {
            return this->data[i].second;
        }
    }
    return nil;
}
