#ifndef KC_UTILITIES_TABLE_H
#define KC_UTILITIES_TABLE_H

#include "Dynar.H"

template<typename Key_T, typename Value_T>
struct TableEntry {
    Key_T Key;
    Value_T Value;
    TableEntry<Key_T, Value_T> *Next;

    TableEntry(Key_T key, Value_T value);
};

template<typename Key_T, typename Value_T, Size Size_V>
class Table {
    TableEntry<Key_T, Value_T> entries[Size_V];

public:
    Table();

public:
    Void Put(Key_T key, Value_T value);

    Value_T *Get(Key_T key);

    Nat64 Hash(Key_T key, Size size);
};

template<typename Value_T, Size Size_V>
using StringTable = Table<const Sym8 *, Value_T, Size_V>;

#endif // KC_UTILITIES_TABLE_H
