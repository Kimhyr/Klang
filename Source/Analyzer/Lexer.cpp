#include "Lexer.hpp"

#include "../Utility/Char.hpp"
#include "../Utility/Dynar.hpp"
#include "../Utility/Text.hpp"

namespace Analyzer {
    using namespace Utility;

    Void Lexer::Destroy() {
        delete[] this->source;
    }

    Lexer::Flag Lexer::Lex(Token *out) {
        while (Char::IsWhitespace(this->peek)) {
            this->Advance();
        }

        out->SetStart(this->point);
        if (Char::IsAlphabetic(this->peek) || this->peek == '_') {
            Dynar<Char8> buf;
            do {
                buf.Put(this->peek);
                this->Advance();
            } while (Char::IsNumeric(this->peek) || Char::IsAlphabetic(this->peek) || this->peek == '_');
            buf.Put('\0');
            Char8 *flush = buf.Flush();
            if (Text::Compare(flush, "procedure") == 0) {
                out->SetSymbol(Token::Symbol::Procedure);
            }
            else if (Text::Compare(flush, "let") == 0) {
                out->SetSymbol(Token::Symbol::Let);
            }
            else if (Text::Compare(flush, "return") == 0) {
                out->SetSymbol(Token::Symbol::Return);
            }
            else {
                out->SetSymbol(Token::Symbol::Identity);
                out->SetValue({.Identity = flush});
            }
        }
        else if (Char::IsNumeric(this->peek)) {
//            Dynar<Char8> buf;
//            switch (this->Peek(2)) {
//            case 'x': case 'X': case 'h': case 'H':
//                // Lex hexidecimal
//            default:
//                out->SetSymbol(Token::Symbol::Integer);
//
//            }
//            do {
//                if (this->peek != '_') {
//                    buf.Put(this->peek);
//                }
//                this->Advance();
//                if (this->peek == '.') {
//                    if (out->GetSymbol() == Token::Symbol::Real) {
//                        throw Error(
//                                this, Error::Severity::Error,
//                                0, "Real literal token has too many dots."
//                        );
//                    }
//                    out->SetSymbol(Token::Symbol::Real);
//                }
//            } while (this->peek == '_' || Char::IsNumeric(this->peek));
//            Char8 *flush = buf.Flush();
//            if (out->GetSymbol() == Token::Symbol::Integer) {
//                out->SetValue({.Integer = flush});
//            } else {
//                out->SetValue({.Real = flush});
//            }
        }
        else {
            switch (this->peek) {
            case '-':
            default:
                out->SetSymbol(this->peek);
                break;
            }
            this->Advance();
        SINGLE:
            this->Advance();
        }

    END:
        out->SetEnd(this->point);
        out->GetEnd()->Column--;
        if (this->peek == '\0') {
            this->flags |= Lexer::Flag::End;
        }
        return this->flags;
    }
} // Analyzer