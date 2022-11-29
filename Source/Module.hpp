#ifndef COMPILER__MODULE_HPP
#define COMPILER__MODULE_HPP

#include "Definitions.hpp"

namespace Compiler {
    class Module {
    public:
        virtual
        const Char8 *GetModuleName() = 0;
    };
};

#endif //COMPILER__MODULE_HPP
