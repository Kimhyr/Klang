#ifndef KPLC__MODULE_HPP
#define KPLC__MODULE_HPP

#include "Definitions.hpp"

namespace Compiler {
    class Module {
    public:
        virtual
        const Char8 *GetModuleName() = 0;
    };
};

#endif //KPLC__MODULE_HPP
