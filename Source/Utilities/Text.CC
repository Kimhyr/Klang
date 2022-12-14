#include "Text.H"

#include <string>

template<typename Sym_T>
Bool Text<Sym_T>::Compare(const Sym_T *first, const Sym_T *second) {
    const Sym_T *text[2] = {first, second};
    while (*text[0] && (*text[0]++ == *text[1]++));
    return *text[0] - *text[1];
}

template<typename Sym_T>
Nat64 Text<Sym_T>::ToNatural(const Sym_T *text, Nat8 base) {
    return std::stoull(text, 0, base);
    // Nat64 result = 0;
    // for (const Sym8 *ptr = text; *ptr;
    //     result = result * base + *ptr++ - '0');
    // return result;
}

template<typename Sym_T>
Int64 Text<Sym_T>::ToInteger(const Sym_T *text, Nat8 base) {
    return std::stoll(text, 0, base);
}

template<typename Sym_T>
Real64 ToReal(const Sym_T*text) {
    return std::stod(text, 0);
}
