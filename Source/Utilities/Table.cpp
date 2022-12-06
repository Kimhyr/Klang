#ifndef KPLC_UTILITIES_TABLE_CPP
#define KPLC_UTILITIES_TABLE_CPP

#include "Dynar.cpp"

namespace U {
    template<typename Key_T, typename Value_T>
    struct TableEntry {
        Key_T Key;
        Value_T Value;
    };

    template<typename Key_T, typename Value_T>
    class Table {
        Dynar<TableEntry<Key_T, Value_T>> entries;

    public:
        Table();
    };
} // U

#endif // KPLC_UTILITIES_TABLE_CPP
