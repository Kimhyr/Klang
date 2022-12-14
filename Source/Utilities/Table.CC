#include "Table.H"

template<typename Key_T, typename Value_T>
TableEntry<Key_T, Value_T>::TableEntry(Key_T key, Value_T value)
    : Key(key),
      Value(value),
      Next(NIL) {}

template<typename Key_T, typename Value_T, Size Size_V>
Table<Key_T, Value_T, Size_V>::Table() {}

template<typename Key_T, typename Value_T, Size Size_V>
Void Table<Key_T, Value_T, Size_V>::Put(Key_T key, Value_T value) {
    Size hash = $ Hash(value);
    if ($ entries[hash] != NIL) {
        $ entries[hash] = TableEntry<Key_T, Value_T>(key, value);
        return;
    }
    TableEntry<Key_T, Value_T> *next = $ entries[hash].Next;
    while (next != NIL)
        next = next->Next;
    next = new TableEntry<Key_T, Value_T>(key, value);
}

template<typename Key_T, typename Value_T, Size Size_V>
Value_T *Table<Key_T, Value_T, Size_V>::Get(Key_T key) {
    Size hash = $ Hash(key);
    if ($ entries[hash] == NIL)
        return NIL;
    TableEntry<Key_T, Value_T> *entry = &$ entries[hash];
    Value_T *value;
    while (entry != NIL) {
        for (Size i = 0; entry->Key[i] != 0; ++i)
            if (entry->Key[i] != key[i]) {
                entry = entry->Next;
                continue;
            }
        value = &entry->Value;
    }
    return value;
}

template<typename Key_T, typename Value_T, Size Size_V>
Size Table<Key_T, Value_T, Size_V>::Hash(Key_T key, Size size) {
    Size result = 0;
    for (Size i = 0; i < size; ++i)
        result += key[i];
    return result % Size_V;
}
