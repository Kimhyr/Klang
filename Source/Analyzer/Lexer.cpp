#include "Lexer.hpp"

#include "../Utility/Char.hpp"
#include "../Utility/Dynar.hpp"
#include "../Utility/Text.hpp"

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

        /*
        Number := Integer       := <INTEGER>+ [<INTEGER>|'_']*
                | Binary        := '0' ['b'|'B'] ['0'|'1'|'_']+
                | Hexadecimal   := '0' ['x'|'X'|'h'|'H'] [<INTEGER>|<ALPHABET:('a'..'f'&'A'..'F')>|'_']+
                | Real          := <INTEGER>+ [<INTEGER>|'_']* ('.' [<INTEGER>|'_']*)?
                | Scientific    := <INTEGER>+ ['E'|'e'] ['+'|'-'] <INTEGER>+k
         */
        else if (Char::IsNumeric(this->peek)) {
            Dynar<Char8> buf;
            if (this->peek == '0') {
                this->Advance();
                switch (this->Peek(2)) {
                case 'b': case 'B':
                    this->Advance();
                    // TODO Refactor this.
                    while (this->peek == '0' || this->peek == '1' || this->peek == '_') {
                        if (this->peek != '_') {
                            buf.Put(this->peek);
                        }
                        this->Advance();
                    }
                    break;
                case 'x': case 'X': case 'h': case 'H':
                    this->Advance();
                    // Lex hexadecimal
                    break;
                default:
                    break;
                }
            }
        }
        else {
            switch (this->peek) {
            case '-':
            default:
                this->token.SetSymbol(this->peek);
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
} // Analyzer