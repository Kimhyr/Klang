#ifndef KPLC__MODULE_HPP
#define KPLC__MODULE_HPP

#include "Definitions.hpp"

namespace Compiler {
    class Module {
    public:
        enum class Identity {
            None,
            Lexer,
            Parser,
            Processor,
            Generator,
        };

    public:
        virtual inline
        Module::Identity GetModuleIdentity()
        const noexcept { return Module::Identity::None; };
    };
};

#endif //KPLC__MODULE_HPP
