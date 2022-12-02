#ifndef KPLC_UTILITY_EXCEPTION_EXCEPTION_HPP
#define KPLC_UTILITY_EXCEPTION_EXCEPTION_HPP

#include "../../Definitions.hpp"

namespace Utility::Exceptions {
    class Exception {
    public:
        enum class From : UInt8 {
            Lexer,
        };

        enum class Severity {
            Verbose,
            Info,
            Warning,
            Error,
        };

    public:
        constexpr
        Exception(
                Exception::From from, Exception::Severity severity,
                UInt64 code, const Char8 *description
        )
                : from(from),
                  severity(severity),
                  code(code),
                  description(description) {}

        Void Destroy();

    public:
        virtual inline constexpr
        Exception::From GetFrom()
        const noexcept { return this->from; }

        virtual inline constexpr
        Exception::Severity GetSeverity()
        const noexcept { return this->severity; }

        virtual inline constexpr
        UInt64 GetCode()
        const noexcept { return this->code; }

        virtual inline constexpr
        const Char8 *GetDescription()
        const noexcept { return this->description; }

    private:
        Exception::From from;
        Exception::Severity severity;
        UInt64 code;
        const Char8 *description;
    };
} // Compiler::Exceptions

#endif // KPLC_UTILITY_EXCEPTION_EXCEPTION_HPP
