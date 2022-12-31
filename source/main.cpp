#include "analyzer/lexer.hpp"
#include "doctor.hpp"

Int main() {
        KC::Lexer lexer("datum value: -32 = (21 + 14) / 8 * (3 % 20) - 7;");
        for (;;) {
                try {
                        KC::Token token = lexer.lex();
                        token.print();
                        if (token.tag == KC::Token::Tag::END)
                                break;
                } catch (KC::Diagnosis) {
                        continue;
                }
        }
        return 0;
}
