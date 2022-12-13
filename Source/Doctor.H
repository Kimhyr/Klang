#ifndef KC_DOCTOR_H
#define KC_DOCTOR_H

#include "Compiler.H"

#include <stdexcept>

struct Diagnosts {
    CompilerModule Module;
    Nat64 Code;
    const Sym8 *Description;

public:
    using OutOfRange = std::out_of_range;
    using InvalidArgument = std::invalid_argument;

public:
    Diagnosts(CompilerModule module, Nat64 code, const Sym8 *description)
        : Module(module),
          Code(code),
          Description(description) {}
};

#endif // KC_DOCTOR_H
