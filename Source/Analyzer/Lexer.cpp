#include "Lexer.hpp"

#include "../Utility/Dynar.hpp"
#include "../Utility/Text.hpp"
#include "../Utility/Error.hpp"

namespace Analyzer {
    using namespace Utility;

    Void Lexer::Destroy() {
        delete[] this->source;
    }

    Token Lexer::Lex() {
        while (Char::IsWhitespace(this->peek)) {
            this->Advance();
        }

        this->token.SetStart(this->point);
        if (Char::IsAlphabetic(this->peek) || this->peek == '_') {
            Dynar<Char8> buf;
            do {
                buf.Put(this->peek);
                this->Advance();
            } while (Char::IsNumeric(this->peek) || Char::IsAlphabetic(this->peek) || this->peek == '_');
            buf.Put('\0');
            Char8 *flush = buf.Flush();
            if (Text::Compare(flush, "procedure") == 0) {
                this->token.SetSymbol(Token::Symbol::Procedure);
            }
            else if (Text::Compare(flush, "let") == 0) {
                this->token.SetSymbol(Token::Symbol::Let);
            }
            else if (Text::Compare(flush, "return") == 0) {
                this->token.SetSymbol(Token::Symbol::Return);
            }
            else {
                this->token.SetSymbol(Token::Symbol::Identity);
                this->token.SetValue({.Identity = flush});
            }
        }
        else if (Char::IsNumeric(this->peek)) {
            Dynar<Char8> buf;
            if (this->peek == '0') {
                this->Advance();
                switch (this->peek) {
                case '0':
                    do {
                        this->Advance();
                    } while (this->peek == '0');
                    break;
                case 'b':
                    this->peek = 'B';
                case 'B':
                    // Lex binary.
                    buf.Put(this->peek);
                    this->Advance();
                    if (Lexer::CharIsBinaryNumber(this->peek)) {
                        do {
                            if (this->peek != '_') {
                                buf.Put(this->peek);
                            }
                            this->Advance();
                        } while (this->peek == '_' || Lexer::CharIsBinaryNumber(this->peek));
                    } else {
                        if (Char::IsNumeric(this->peek)) {}
                        // Binary is incomlete
                    }
                    break;
                case 'x':
                    this->peek = 'X';
                case 'X':
                    // Lex Hexadecimal.
                    break;
                }
            }
        }
        else {
            switch (this->peek) {
            case '-':
            default:
                this->token.SetSymbol((Token::Symbol)this->peek);
                break;
            }
            this->Advance();
        SINGLE:
            this->Advance();
        }

    END:
        this->token.SetEnd(this->point);
        this->token.SetEnd(
                {
                        .Line = this->point.Line,
                        .Column = this->point.Column - 1
                }
        );
        if (this->peek == '\0') {
            this->flags |= Lexer::Flag::End;
        }
        return this->token;
    }

    Void Lexer::LexNaturalNumber(Dynar<Char8> *buf) {
        do {
            if (this->peek != '_') {
                buf->Put(this->peek);
            }
            this->Advance();
        } while (Lexer::CharIsNaturalNumber(this->peek));
    }
} // Analyzer