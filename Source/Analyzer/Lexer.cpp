#ifndef KPLC_ANALYZER_LEXER_CPP
#define KPLC_ANALYZER_LEXER_CPP

#include "../Exception.cpp"
#include "../Utilities/Text.cpp"
#include "../Utilities/Dynar.cpp"
#include "Token.cpp"

class Lexer {
public:
    enum class Module : Nat8 {
        Alphabetic,
        Numeric,
        Natural,
        Binary,
        Hexadecimal,
        Real,
        Scientific,
        Symbolic,
    };

    enum Flag : Bit8 {
        End = 1 << 0,
        Continue = 1 << 1,
    };

    enum class ErrorCode : Nat8 {
        WrongFormat = 1,
        Valueless,
        Incomplete,
        Inconvertible,
        OutOfRange,
    };

public:
    [[nodiscard]]
    explicit constexpr
    Lexer(const Text8 *source)
        : point({1, 1}),
          index(-1),
          source(source),
          peek(source[0]),
          token() {}

    Void Destroy() { delete[] $ source; }

public:
    Token Lex() {
        while (U::Text::IsWhitespace($ peek))
            $ Advance();
        if ($ peek == '\0') {
            $ token.Symbol = Token::Symbol::End;
            goto EPILOGUE;
        }

        $ token.Start = $ point;
        if (U::Text::IsAlphabetic($ peek))
            $ LexAlphabetic();
        else if (U::Text::IsNumeric($ peek))
            $ LexNumeric();
        else $ LexSymbolic();

    EPILOGUE:
        $ token.End = {
            .Line = $ point.Line,
            .Column = $ point.Column - 1
        };
        return $ token;
    }

private:
    Token::Point point;
    Int64 index;
    const Text8 *source;
    Text8 peek;
    Token token;

private:
    [[nodiscard]]
    constexpr
    Bool PeekIsValidIdentity()
    const noexcept { return U::Text::IsAlphabetic($ peek) || $ peek == '_'; }

    Void LexAlphabetic() {
        U::Dynar<Text8> buf;
        do {
            if (buf.Size() > 1024)
                $ Yeet(Lexer::Module::Alphabetic, Lexer::ErrorCode::OutOfRange);
            buf.Put($ peek);
            $ Advance();
        } while (U::Text::IsNumeric($ peek) || $ PeekIsValidIdentity());
        buf.Put('\0');
        $ MatchWord(buf.Flush());
    }

    Void MatchWord(const Text8 *buf) {
        if (U::Text::Compare("procedure", buf) == 0)
            $ token.Symbol = Token::Symbol::Procedure;
        else if (U::Text::Compare("datum", buf) == 0)
            $ token.Symbol = Token::Symbol::Datum;
        else if (U::Text::Compare("give", buf) == 0)
            $ token.Symbol = Token::Symbol::Give;
        
        // TODO This shit could be more efficient.
        else if (U::Text::Compare("Nat8", buf) == 0)
            $ token.Symbol = Token::Symbol::Nat8;
        else if (U::Text::Compare("Nat16", buf) == 0)
            $ token.Symbol = Token::Symbol::Nat16;
        else if (U::Text::Compare("Nat32", buf) == 0)
            $ token.Symbol = Token::Symbol::Nat32;
        else if (U::Text::Compare("Nat64", buf) == 0)
            $ token.Symbol = Token::Symbol::64;
        else if (U::Text::Compare("Int8", buf) == 0)
            $ token.Symbol = Token::Symbol::Nat8;
        else if (U::Text::Compare("Int16", buf) == 0)
            $ token.Symbol = Token::Symbol::Nat16;
        else if (U::Text::Compare("Int32", buf) == 0)
            $ token.Symbol = Token::Symbol::Nat32;
        else if (U::Text::Compare("Int64", buf) == 0)
            $ token.Symbol = Token::Symbol::64;
        else {
            $ token.Symbol = Token::Symbol::Identity;
            $ token.Value.Identity = buf;
        }
    }

private:
    inline
    Void LexNumeric() {
        U::Dynar<Text8> buf;
        if ($ peek == '0') {
            $ Advance();
            switch ($ peek) {
            case '0':
                do $ Advance();
                while ($ peek == '0');
                break;
            case 'b':
            case 'B':
                $ Advance();
                return $ LexBinary(&buf);
            case 'x':
            case 'X':
                $ Advance();
                return $ LexHexadecimal(&buf);
            default:
                break;
            }
        }

        if ($ PeekIsValidNatural())
            return $ LexNatural(&buf);
        else if ($ peek == '.')
            return $ LexReal(&buf);
        $ token.Symbol = Token::Symbol::Natural;
        $ token.Value.Integer = 0;
    }

    inline
    Void PutNumericBuf(U::Dynar<Text8> *buf) {
        if ($ peek != '_')
            buf->Put($ peek);
        $ Advance();
    }

private:
    [[nodiscard]]
    constexpr
    Bool PeekIsValidBinary()
    const noexcept { return $ peek == '0' || $ peek == '1' || $ peek == '_'; }

    inline
    Void BinaryYeet(Lexer::ErrorCode error) { $ Yeet(Lexer::Module::Binary, error); }

    inline
    Void LexBinary(U::Dynar<Text8> *buf) {
        $ token.Symbol = Token::Symbol::Machine;
        if ($ PeekIsValidBinary()) {
            do $ PutNumericBuf(buf);
            while ($ PeekIsValidBinary());
        } else $ BinaryYeet(Lexer::ErrorCode::WrongFormat);

        if (buf->Size() == 0)
            $ BinaryYeet(Lexer::ErrorCode::Valueless);
        buf->Put(0);
        try {
            $ token.Value.Machine = U::Text::ConvertToNatural(buf->Flush(), 2);
        } catch (const Exception::InvalidArgument &) {
            $ BinaryYeet(Lexer::ErrorCode::Inconvertible);
        } catch (const Exception::OutOfRange &) {
            $ BinaryYeet(Lexer::ErrorCode::OutOfRange);
        }
    }

private:
    [[nodiscard]]
    constexpr
    Bool PeekIsValidHexadecimal()
    const noexcept {
        return ($ peek >= 'a' && $ peek <= 'f') ||
               ($ peek >= 'A' && $ peek <= 'F') || $ PeekIsValidNatural();
    }

    inline
    Void HexadecimalYeet(Lexer::ErrorCode error) { $ Yeet(Lexer::Module::Hexadecimal, error); }

    inline
    Void LexHexadecimal(U::Dynar<Text8> *buf) {
        $ token.Symbol = Token::Symbol::Machine;
        if ($ PeekIsValidHexadecimal()) {
            do $ PutNumericBuf(buf);
            while ($ PeekIsValidHexadecimal());
        } else $ HexadecimalYeet(Lexer::ErrorCode::WrongFormat);

        if (buf->Size() == 0)
            HexadecimalYeet(Lexer::ErrorCode::Valueless);
        buf->Put(0);
        try {
            $ token.Value.Machine = U::Text::ConvertToNatural(buf->Flush(), 16);
        }
        catch (const Exception::InvalidArgument &) {
            $ HexadecimalYeet(Lexer::ErrorCode::Inconvertible);
        }
        catch (const Exception::OutOfRange &) {
            $ HexadecimalYeet(Lexer::ErrorCode::OutOfRange);
        }
    }

private:
    [[nodiscard]]
    constexpr
    Bool PeekIsValidNatural()
    const noexcept { return U::Text::IsNumeric($ peek) || $ peek == '_'; }

    inline
    Void NaturalYeet(Lexer::ErrorCode error) { $ Yeet(Lexer::Module::Natural, error); }

    Void LexNatural(U::Dynar<Text8> *buf) {
        do {
            $ PutNumericBuf(buf);
            if ($ peek == '.')
                return $ LexReal(buf);
        } while ($ PeekIsValidNatural());
        $ token.Symbol = Token::Symbol::Natural;

        if (buf->Size() == 0)
            $ NaturalYeet(Lexer::ErrorCode::Valueless);
        buf->Put(0);
        try {
            $ token.Value.Integer = U::Text::ConvertToInteger(buf->Flush());
        } catch (const Exception::InvalidArgument &) {
            $ NaturalYeet(Lexer::ErrorCode::Inconvertible);
        } catch (const Exception::OutOfRange &) {
            $ NaturalYeet(Lexer::ErrorCode::OutOfRange);
        }
    }

private:
    inline
    Void RealYeet(Lexer::ErrorCode error) { $ Yeet(Lexer::Module::Real, error); }

    Void LexReal(U::Dynar<Text8> *buf) {
        $ token.Symbol = Token::Symbol::Real;
        do {
            $ PutNumericBuf(buf);
            if ($ peek == '.')
                $ RealYeet(Lexer::ErrorCode::WrongFormat);
        } while ($ PeekIsValidNatural());

        buf->Put(0);
        try {
            $ token.Value.Real = U::Text::ConvertToReal(buf->Flush());
        } catch (const Exception::InvalidArgument &) {
            $ RealYeet(Lexer::ErrorCode::Inconvertible);
        } catch (const Exception::OutOfRange &) {
            $ RealYeet(Lexer::ErrorCode::OutOfRange);
        }
    }

private:
    Void LexSymbolic() {
        switch () {
    
  }    
    }

private:
    Void Yeet(Lexer::Module way, Lexer::ErrorCode error) {
        const Text8 *description = "";
        throw Exception(
            Compiler::Module::Lexer, Exception::Type::Error,
            (Nat64) error + (Nat64) way, description
        );
    }

private:
    [[nodiscard]]
    constexpr
    Text8 Peek(Nat64 offset = 1)
    const noexcept { return $ source[$ index + offset]; }

    constexpr
    Void Advance()
    noexcept {
        $ index++;
        $ peek = $ Peek();
        if ($ peek == '\n') {
            $ point.Line++;
            $ point.Column = 0;
        }
        $ point.Column++;
    }
};

#endif // KPLC_ANALYZER_LEXER_CPP
