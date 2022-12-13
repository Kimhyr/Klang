#include <iostream>

#include "Analyzer/Lexer.cpp"
#include "Definitions.cpp"

class Bit {
public:
    static
    Bool Check(Bit8 bits, Nat8 index) {
        return bits & (1 << (index - 1));
    }
};

Int32 main() {
    Lexer lexer(
        "procedure 234234 sdaf  asdf124312a 0x23_z_4 0b010101___0 0.23______432 234234.");
    Token token {};
    do {
        try {
            token = lexer.Lex();
        } catch (const Exception &e) {
            std::cout << "Exception Code: " << e.Code << '\n';
            continue;
        }
        switch (token.Symbol) {
        case Token::Symbol::Identity:
            std::cout << "Identity: " << token.Value.Identity << '\n';
            break;
        case Token::Symbol::Natural:
            std::cout << "Natural: " << token.Value.Natural << '\n';
            break;
        case Token::Symbol::Integer:
            std::cout << "Integer: " << token.Value.Integer << '\n';
            break;
        case Token::Symbol::Real:
            std::cout << "Real: " << token.Value.Real << '\n';
            break;
        case Token::Symbol::Machine:
            std::cout << "Machine: " << token.Value.Machine << '\n';
            break;
        default:
            break;
        }
    } while (token.Symbol != Token::Symbol::End);
    return 0;
}
