#include "Error.hpp"

#include <iostream>

namespace Utility {
    Void Error::Destroy() {
        delete[] this->description;
    }

    Void Error::Send() {
        switch (this->severity) {
        case Error::Severity::Verbose:
            std::cerr << "[Verbose] ";
        case Error::Severity::Info:
            std::cerr << "[Info] ";
        case Error::Severity::Warning:
            std::cerr << "[Warning] ";
        case Error::Severity::Error:
            std::cerr << "[Error] ";
        }
        std::cerr << this->module->GetModuleName()
                  << " (" << this->code << "): "
                  << this->description << '\n';
        this->Destroy();
    }
} // Utility