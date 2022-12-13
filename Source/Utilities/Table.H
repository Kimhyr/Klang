#ifndef KC_UTILITIES_TABLE_H
#define KC_UTILITIES_TABLE_H

#include "../Include.H"

namespace U {
    template<typename Key_T, typename Value_T>
    struct TableEntry {
        Key_T Key;
        Value_T Value;
    };

    template<typename Key_T, typename Value_T>
    class Table {
        TableEntry<Key_T, Value_T> *entries;

    public:
        Result Get(Key_T key, Value_T *out);
    };
} // U

#endif // KC_UTILITIES_TABLE_H
