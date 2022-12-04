#include "Lexer.hpp"

#include "../../Utility/Exceptions/Exception.hpp"
#include "../../Utility/Exceptions/InvalidArgument.hpp"
#include "../../Utility/Exceptions/OutOfRange.hpp"
#include "../../Utility/Text/String.hpp"

namespace Compiler::Analyzer {
    using namespace Utility::Exceptions;

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

    Void Lexer::LexAlphabetic()
    noexcept {
        Dynar<Text8> buf;
        do {
            buf.Put(this->peek);
            this->Advance();
        } while (Char::IsNumeric(this->peek) || Char::IsAlphabetic(this->peek) || this->peek == '_');
        buf.Put('\0');
        Text8 *flush = buf.Flush();
        this->MatchAlphabetic(flush);
    }

    Void Lexer::MatchAlphabetic(const Text8 *flush)
    noexcept {
        if (String::Compare(flush, "procedure") == 0) {
            this->token.SetSymbol(Token::Symbol::Procedure);
        }
        else if (String::Compare(flush, "let") == 0) {
            this->token.SetSymbol(Token::Symbol::Datum);
        }
        else if (String::Compare(flush, "return") == 0) {
            this->token.SetSymbol(Token::Symbol::Give);
        }
        else {
            this->token.SetSymbol(Token::Symbol::Identity);
            this->token.SetValue({.Identity = flush});
        }
    }

    Void Lexer::LexNumeric() {
        Dynar<Text8> buf;
        if (this->peek == '0') {
            this->Advance();
            switch (this->peek) {
            case '0':
                this->SkipZeros();
                break;
            case 'b':
            case 'B':
                this->Advance();
                this->LexBinaryLiteral(&buf);
                break;
            case 'x':
            case 'X':
                this->Advance();
                return this->LexHexadecimalLiteral(&buf);
            default:
                break;
            }
        }
        if (this->PeekIsValidUnsigned()) {
            this->LexNaturalLiteral(&buf);
        }
        else if (this->peek == '.') {
            this->LexReal(&buf);
        }
        else {
            this->token.SetSymbol(Token::Symbol::Natural);
            this->token.SetValue({.Integer = 0});
        }
    }

    Void Lexer::LexNaturalLiteral(Dynar<Text8> *buf) {
        do {
            this->PutNumericBuf(buf);
            if (this->peek == '.') {
                return this->LexReal(buf);
            }
        } while (this->PeekIsValidUnsigned());
        this->token.SetSymbol(Token::Symbol::Natural);
        if (buf->GetSize() == 0) {
            Lexer::ThrowException(Lexer::Way::NaturalLiteral, Lexer::ErrorCode::Valueless);
        }
        try {
            this->token.SetValue(
                {
                    .Integer = String::ConvertToInteger<Int64>(buf->Flush())
                }
            );
        }
        catch (const Exceptions::InvalidArgument &) {
            Lexer::ThrowException(Lexer::Way::NaturalLiteral, Lexer::ErrorCode::Conversion);
        }
        catch (const Exceptions::OutOfrange &) {
            Lexer::ThrowException(Lexer::Way::NaturalLiteral, Lexer::ErrorCode::OutOfRange);
        }
    }

    Void Lexer::PutNumericBuf(Dynar<Text8> *buf) {
        if (this->peek != '_') {
            buf->Put(this->peek);
        }
        this->Advance();
    }

    Void Lexer::LexBinaryLiteral(Dynar<Text8> *buf) {
        this->token.SetSymbol(Token::Symbol::Machine);
        if (this->PeekIsValidBinary()) {
            do {
                this->PutNumericBuf(buf);
            } while (this->PeekIsValidBinary());
        }
        else {
            if (Char::IsWhitespace(this->peek)) {
                Lexer::ThrowException(Lexer::Way::BinaryLiteral, Lexer::ErrorCode::Incomplete);
            }
            else if (Char::IsAlphabetic(this->peek) || Char::IsNumeric(this->peek)) {
                Lexer::ThrowException(Lexer::Way::BinaryLiteral, Lexer::ErrorCode::WrongFormat);
            }
        }
        if (buf->GetSize() == 0) {
            Lexer::ThrowException(Lexer::Way::BinaryLiteral, Lexer::ErrorCode::Valueless);
        }
        try {
            this->token.SetValue(
                {
                    .Machine = String::ConvertToInteger<Nat64>(buf->Flush(), 2)
                }
            );
        }
        catch (const Exceptions::InvalidArgument &) {
            Lexer::ThrowException(Lexer::Way::BinaryLiteral, Lexer::ErrorCode::Conversion);
        }
        catch (const Exceptions::OutOfrange &) {
            Lexer::ThrowException(Lexer::Way::BinaryLiteral, Lexer::ErrorCode::OutOfRange);
        }
    }

    Void Lexer::LexHexadecimalLiteral(Dynar<Text8> *buf) {
        this->token.SetSymbol(Token::Symbol::Machine);
        if (this->PeekIsValidHexadecimal()) {
            do {
                this->PutNumericBuf(buf);
            } while (this->PeekIsValidHexadecimal());
        }
        else {
            if (Char::IsWhitespace(this->peek)) {
                Lexer::ThrowException(Lexer::Way::HexadecimalLiteral, Lexer::ErrorCode::Incomplete);
            }
            else if (Char::IsAlphabetic(this->peek)) {
                Lexer::ThrowException(Lexer::Way::HexadecimalLiteral, Lexer::ErrorCode::WrongFormat);
            }
        }
        if (buf->GetSize() == 0) {
            Lexer::ThrowException(Lexer::Way::HexadecimalLiteral, Lexer::ErrorCode::Valueless);
        }
        try {
            this->token.SetValue(
                {
                    .Machine = String::ConvertToInteger<Nat64>(buf->Flush(), 16)
                }
            );
        }
        catch (const Exceptions::InvalidArgument &) {
            Lexer::ThrowException(Lexer::Way::HexadecimalLiteral, Lexer::ErrorCode::Conversion);
        }
        catch (const Exceptions::OutOfrange &) {
            Lexer::ThrowException(Lexer::Way::HexadecimalLiteral, Lexer::ErrorCode::OutOfRange);
        }
    }

    Void Lexer::LexReal(Dynar<Text8> *buf) {
        // TODO This shit
        this->token.SetSymbol(Token::Symbol::Real);
        do {
            this->PutNumericBuf(buf);
            if (this->peek == '.') {
                Lexer::ThrowException(Lexer::Way::RealLiteral, Lexer::ErrorCode::WrongFormat);
            }
        } while (this->PeekIsValidUnsigned());
        try {
            this->token.SetValue(
                {
                    .Float = String::ConvertToFloat<Float64>(buf->Flush())
                }
            );
        }
        catch (const Exceptions::InvalidArgument &) {
            Lexer::ThrowException(Lexer::Way::RealLiteral, Lexer::ErrorCode::Conversion);
        }
        catch (const Exceptions::OutOfrange &) {
            Lexer::ThrowException(Lexer::Way::RealLiteral, Lexer::ErrorCode::OutOfRange);
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

    Void Lexer::ThrowException(Lexer::Way way, Lexer::ErrorCode error) {
        const Text8 *description = "";
        throw Exception(
            Exception::From::Lexer, Exception::Severity::Error,
            // Adding so I don't get an error due to `-Werror`
            (Nat64) error + (Nat64) way, description
        );
    }
} // Analyzer
