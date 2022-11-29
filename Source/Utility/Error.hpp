#ifndef KPLC_UTILITY_ERROR_HPP
#define KPLC_UTILITY_ERROR_HPP

#include "../Definitions.hpp"
#include "../Module.hpp"

namespace Utility {
    class Error {
    public: // Types
        enum class Severity {
            Verbose,
            Info,
            Warning,
            Error,
        };

    public: // Constructors and destructors
        constexpr
        Error(
                const Compiler::Module *module, Error::Severity severity,
                UInt64 code, const Char8 *description
        )
                : module(module),
                  severity(severity),
                  code(code),
                  description(description) {}

        Void Destroy();

        Void Send();

    public: // Properties
        inline constexpr
        const Compiler::Module *GetModule()
        const noexcept { return &this->module; }

        inline constexpr
        Error::Severity GetSeverity()
        const noexcept { return this->severity; }

        inline constexpr
        UInt64 GetCode()
        const noexcept { return this->code; }

        inline constexpr
        const Char8 *GetDescription()
        const noexcept { return this->description; }

    private: // Properties
        const Compiler::Module *module;
        Error::Severity severity;
        UInt64 code;
        const Char8 *description;
    };
} // Utility

#endif // KPLC_UTILITY_ERROR_HPP
