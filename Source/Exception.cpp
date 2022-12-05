#ifndef KPLC_EXCEPTION_CPP
#define KPLC_EXCEPTION_CPP

#include <stdexcept>

#include "Compiler.cpp"
#include "Definitions.cpp"

struct Exception {
    using OutOfRange = std::out_of_range;
    using InvalidArgument = std::invalid_argument;

    enum class Type {
        Verbose,
        Info,
        Warning,
        Error,
    };

    Compiler::Module CompilerModule;
    Exception::Type ExceptionType;
    Nat64 Code;
    const Text8 *Description;

    constexpr
    Exception(
        Compiler::Module compilerModule, Type exceptionType,
        Nat64 code, const Text8 *description
    )
        : CompilerModule(compilerModule),
          ExceptionType(exceptionType),
          Code(code),
          Description(description) {}

    Void Destroy() { delete[] $ Description; }
};

#endif // KPLC_EXCEPTION_CPP
