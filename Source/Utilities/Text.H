#ifndef KC_UTILITIES_TEXT_H
#define KC_UTILITIES_TEXT_H

#include "../Include.H"

template<typename Sym_T>
class Text {
public:
    static
    Bool Compare(const Sym_T *first, const Sym_T *second);

public:
    static
    Bool ToNatural(Nat64 *out, const Sym_T *text, Nat8 base = 10);

    static
    Bool ToInteger(Int64 *out, const Sym_T *text, Nat8 base = 10);

    static
    Bool ToReal(Real64 *out, const Sym_T *text);

public:
    static constexpr
    Bool IsWhitespace(Sym_T text) {
        return (text == ' ') || (text >= '\t' && text <= '\r');
    }

    static constexpr
    Bool IsAlphabetic(Sym_T text) {
        return (text >= 'A' && text <= 'Z') || (text >= 'a' && text <= 'z');
    }

    static constexpr
    Bool IsNumeric(Sym_T text) {
        return text >= '0' && text <= '9';
    };
};

using Text8 = Text<Sym8>;

#endif // KC_UTILITIES_TEXT_H
