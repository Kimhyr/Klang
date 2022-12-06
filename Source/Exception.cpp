#ifndef KPLC_EXCEPTION_CPP
#define KPLC_EXCEPTION_CPP

#include <stdexcept>

#include "Compiler.cpp"
#include "Definitions.cpp"

struct Exception {
    CompilerModule Module;
    Nat64 Code;
    const Text8 *Description;

public:
    using OutOfRange = std::out_of_range;
    using InvalidArgument = std::invalid_argument;

public:
    constexpr
    Exception(
        CompilerModule module,
        Nat64 code, const Text8 *description
    )
        : Module(module),
          Code(code),
          Description(description) {}

    Void Destroy() { delete[] $ Description; }
};

#endif // KPLC_EXCEPTION_CPP
