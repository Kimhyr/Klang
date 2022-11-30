#ifndef KPLC_COMPILER_ERROR_HPP
#define KPLC_COMPILER_ERROR_HPP

#include "../Definitions.hpp"

namespace Compiler {
    class Error {
    public:
        using Code = UInt64;

        enum class Severity {
            Verbose,
            Info,
            Warning,
            Error,
        };

    public:
        constexpr
        Error(
                Error::Severity severity, Error::Code code,
                const Char8 *description
        )
                : module(module),
                  severity(severity),
                  code(code),
                  description(description) {}

        Void Destroy();

        Void Send();

    public:
        inline constexpr
        Error::Severity GetSeverity()
        const noexcept { return this->severity; }

        inline constexpr
        UInt64 GetCode()
        const noexcept { return this->code; }

        inline constexpr
        const Char8 *GetDescription()
        const noexcept { return this->description; }

    private:
        Error::Severity severity;
        UInt64 code;
        const Char8 *description;
    };
} // Debugger

#endif // KPLC_COMPILER_ERROR_HPP
