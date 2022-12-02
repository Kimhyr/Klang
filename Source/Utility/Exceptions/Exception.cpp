#include "Exception.hpp"

namespace Utility::Exceptions {
    Void Exception::Destroy() {
        delete[] this->description;
    }
} // Compiler
