#include "Text.H"

#include <exception>
#include <string>

template<typename Sym_T>
Bool Text<Sym_T>::Compare(const Sym_T *first, const Sym_T *second) {
    const Sym_T *text[2] = {first, second};
    while (*text[0] && (*text[0]++ == *text[1]++));
    return *text[0] - *text[1];
}

template<typename Sym_T>
Bool Text<Sym_T>::ToNatural(Nat64 *out, const Sym_T *text, Nat8 base) {
    try {
        *out = std::stoull(text, 0, base);
    } catch (const std::exception &) {
        out = NIL;
    }
    // Nat64 result = 0;
    // for (const Sym8 *ptr = text; *ptr;
    //     result = result * base + *ptr++ - '0');
    // return result;
}

template<typename Sym_T>
Bool Text<Sym_T>::ToInteger(Int64 *out, const Sym_T *text, Nat8 base) {
    try {
        *out = std::stoll(text, 0, base);
    } catch (const std::exception &) {
        out = NIL;
    }
}

template<typename Sym_T>
Bool ToReal(Real64 *out, const Sym_T*text) {
    try {
        *out = std::stod(text, 0);
    } catch (const std::exception &) {
        out = NIL;
    }
}
