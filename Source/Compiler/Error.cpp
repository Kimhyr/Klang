#include "Error.hpp"

#include <iostream>

namespace Compiler {
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
        std::cerr << "From ";
        switch (this->from) {
        case Error::From::Lexer:
            std::cerr << "lexer ";
        }
        std::cerr << "(" << this->code << "): ";
        std::cerr << this->description << '\n';
        this->Destroy();
    }
} // Debugger