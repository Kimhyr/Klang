#ifndef KC_UTILITIES_TABLE_H
#define KC_UTILITIES_TABLE_H

namespace U {
    template<typename Key_T, typename Value_T>
    struct TableEntry {
        Key_T Key;
        Value_T Value;
    };
} // U

#endif // KC_UTILITIES_TABLE_H
