#ifndef KPLC_UTILITIES_TABLE_CPP
#define KPLC_UTILITIES_TABLE_CPP

#include "Dynar.cpp"

namespace U {
    template<typename Key_T, typename Value_T>
    class Table {
    public:
        struct Entry {
            Key_T Key;
            Value_T Value;
        };

    public:
        Table();

    private:
        Dynar<Table::Entry> entries;

    private:

    };
} // U

#endif // KPLC_UTILITIES_TABLE_CPP
