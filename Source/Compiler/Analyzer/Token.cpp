#include "Token.hpp"

namespace Compiler::Analyzer {
    Void Token::Destroy() {
        switch (this->symbol) {
        case Token::Symbol::Identity:
            delete[] this->value.Identity;
            return;
        case Token::Symbol::Text:
        case Token::Symbol::CText:
            delete[] this->value.Text;
            return;
        default:
            return;
        }
    }
} // Analyzer