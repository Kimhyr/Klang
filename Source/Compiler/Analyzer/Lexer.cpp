#include "Lexer.hpp"

#include <string>

#include "../../Text/String.hpp"

namespace Compiler::Analyzer {
    Void Lexer::Destroy() {
        delete[] this->source;
    }

    Token Lexer::Lex() {
        this->SkipWhitespace();

        this->token.SetStart(this->point);
        if (Char::IsAlphabetic(this->peek) || this->peek == '_') {
            this->LexAlphabetic();
        }
        else if (Char::IsNumeric(this->peek)) {
            this->LexNumeric();
        }
        else {
            this->LexSymbolic();
        }

        this->ResolveToken();
        return this->token;
    }

    Void Lexer::LexAlphabetic() {
        Dynar<Char8> buf;
        do {
            buf.Put(this->peek);
            this->Advance();
        } while (Char::IsNumeric(this->peek) || Char::IsAlphabetic(this->peek) || this->peek == '_');
        buf.Put('\0');
        Char8 *flush = buf.Flush();
        this->MatchAlphabetic(flush);
    }

    Void Lexer::MatchAlphabetic(const Char8 *flush) {
        if (Text::Compare(flush, "procedure") == 0) {
            this->token.SetSymbol(Token::Symbol::ProcedureKeyword);
        }
        else if (Text::Compare(flush, "let") == 0) {
            this->token.SetSymbol(Token::Symbol::LetKeyword);
        }
        else if (Text::Compare(flush, "return") == 0) {
            this->token.SetSymbol(Token::Symbol::ReturnKeyword);
        }
        else {
            this->token.SetSymbol(Token::Symbol::Identity);
            this->token.SetValue({.Identity = flush});
        }
    }

    Void Lexer::LexNumeric() {
        Dynar<Char8> buf;
        if (this->peek == '0') {
            this->Advance();
            switch (this->peek) {
            case '0':
                this->SkipZeros();
                break;
            case 'b':
                this->peek = 'B';
            case 'B':
                this->Advance();
                this->LexBinary(&buf);
                break;
            case 'x':
                this->peek = 'X';
            case 'X':
                this->Advance();
                this->LexHexadecimal(&buf);
                break;
            }
        }
    }

    Void Lexer::LexBinary(Dynar<Char8> *buf) {
        this->token.SetSymbol(Token::Symbol::MachineLiteral);
        if (this->PeekIsValidBinary()) {
            do {
                if (this->peek != '_') {
                    buf->Put(this->peek);
                }
                this->Advance();
            } while (this->PeekIsValidBinary());
        } else {
            if (Char::IsWhitespace(this->peek)) {
                throw Error(
                        // TODO Refactor error messages to follow D.R.Y..
                        Error::Severity::Error, Lexer::ErrorCode::Incomplete,
                        "Hexadecimal literal token is incomplete.\n"
                        "\tThe header follows with whitespace."
                );
            }
            if (Char::IsAlphabetic(this->peek)) {
                throw Error(
                        Error::Severity::Error, Lexer::ErrorCode::WrongFormat,
                        "Binary literal token has the wrong format.\n"
                        "\tExpected a valid binary character, "
                        "but received an alphabetic character."
                );
            }
            if (Char::IsNumeric(this->peek)) {
                throw Error(
                        Error::Severity::Error, Lexer::ErrorCode::WrongFormat,
                        "Binary literal token has the wrong format.\n"
                        "\tExpected a valid binary character, "
                        "but received a numeric character that is not '1' or '0'."
                );
            }
        }
        if (buf->GetSize() == 0) {
            throw Error(
                    Error::Severity::Error, Lexer::ErrorCode::Valueless,
                    "Binary literal token has no value.\n"
                    "\tIt only contains '_'."
            );
        }

        try {
            this->token.SetValue({.Machine = std::stoull(buf->Flush(), 0, 2)});
        } catch (const auto &) {
            throw Error(
                    Error::Severity::Error, Lexer::ErrorCode::Conversion,
                    "Binary literal token could not be converted into a literal value."
            );
        }
    }

    Void Lexer::LexHexadecimal(Dynar<Char8> *buf) {
        this->token.SetSymbol(Token::Symbol::MachineLiteral);
        if (this->PeekIsValidHexadecimal()) {
            do {
                if (this->peek != '_') {
                    buf->Put(this->peek);
                }
                this->Advance();
            } while (this->PeekIsValidHexadecimal());
        } else {
            if (Char::IsWhitespace(this->peek)) {
                throw Error(
                        Error::Severity::Error, Lexer::ErrorCode::Incomplete,
                        "Hexadecimal literal token is incomplete.\n"
                        "\tThe header follows with whitespace."
                );
            }
            if (Char::IsAlphabetic(this->peek)) {
                throw Error(
                        Error::Severity::Error, Lexer::ErrorCode::WrongFormat,
                        "Hexadecimal literal token has the wrong format.\n"
                        "\tExpected an alphabetic character greater than 'a' and less than 'f', "
                        "or greater than 'A' and less than 'F', "
                        "but received a different alphabetic character."
                );
            }
        }
        if (buf->GetSize() == 0) {
            throw Error(
                    Error::Severity::Error, Lexer::ErrorCode::Valueless,
                    "Hexadecimal literal token has no value.\n"
                    "\tIt only contains '_'."
            );
        }

        try {
           this->token.Setvalue({.Machine = std::stoull(buf->flush(), 0, 12)});
        } catch (const auto &) {
            throw Error(
                    Error::Severity::Error, Lexer::ErrorCode::Conversion,
                    "Hexadecimal literal token could not be converted into a literal value."
            );
        }
    }

    Void Lexer::LexReal(Dynar<Char8> *buf) {
        this->token.SetSymbol(Token::Symbol::FloatLiteral);

        // TODO ...

        try {
            this->token.SetValue({.Float = std::stod(buf->Flush())});
        } catch (const auto &) {
            throw Error(
                    Error::Code::Error, Lexer::ErrorCode::Conversion,
                    "Real literal token could not be converted into a literal value."
            );
        }
    }

    Void Lexer::SkipZeros()
    noexcept {
        do {
            this->Advance();
        } while (this->peek == '0');
    }

    Void Lexer::LexSymbolic() {

    }

    Void Lexer::SkipWhitespace() {
        while (Char::IsWhitespace(this->peek)) {
            this->Advance();
        }
    }

    Void Lexer::ResolveToken() {
        this->token.SetEnd(
                {
                        .Line = this->point.Line,
                        .Column = this->point.Column - 1
                }
        );
        if (this->peek == '\0') {
            this->flags |= Lexer::Flag::End;
        }
    }
} // Analyzer
