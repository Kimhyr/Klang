#include "analyzer/lexer.h"
#include "doctor.h"

using namespace KC;
using namespace KC::Analyzer;

Int main() {
        Lexer lexer("datum value: -32 = (21 + 14) / 8 * (3 % 20) - 7;");
        for (;;) {
                try {
                        Token token = lexer.lex();
                        token.print();
                        if (token.tag == Token::Tag::END)
                                break;
                } catch (KC::Diagnosis) {
                        continue;
                }
        }
        return 0;
}
