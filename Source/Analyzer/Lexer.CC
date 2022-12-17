#include "Lexer.H"

#include "../Utilities/Buffer.H"
#include "../Doctor.H"
#include <corecrt_math.h>

Void Lexer::Destroy() {
    delete[] $ source;
}

Result Lexer::Lex(Token *token) {
    Result result = Result::SUCCESS;
    while (Text8::IsWhitespace($ peek))
        $ Advance();
    token->Start = $ point;
    if ($ peek == '\0') {
        token->Kind = Token::END;
        goto Epilogue;
    }

    if (Text8::IsAlphabetic($ peek) || $ peek == '_') {
        Buffer<Sym8, Lexer::MAX_IDENTIFIER_LENGTH> buffer;
        do {
            if (!buffer.Put($ peek)) {
                Doctor::Diagnose("Buffer overflow!");
                goto Failure;
            }
            $ Advance();
        } while (Text8::IsNumeric($ peek) || Text8::IsAlphabetic($ peek) || $ peek == '_');
        buffer.Put('\0');
        Token::Id *keyword = Lexer::KEYWORD_TABLE.Get(buffer.GetData());
        if (keyword)
            token->Kind = *keyword;
        else {
            token->Kind = Token::IDENTIFIER;
            token->Value.Identifier = buffer.Flush();
        }
        goto Epilogue;
    } else if (Text8::IsNumeric($ peek)) {
        Buffer<Sym8, Lexer::MAX_NUMBER_LENGTH> buffer;
        if ($ peek == '0') {
            $ Advance();
            switch ($ peek) {
            case '0':
                do $ Advance();
                while ($ peek == '0');
                break;
            case 'b': case 'B':
                $ Advance();
                token->Kind = Token::MACHINE;
                if ($ peek == '0' || $ peek == '1') {
                    Doctor::Diagnose("Binary literal has the wrong format.`");
                    goto Failure;
                } do {
                    if (!buffer.Put($ peek)) {
                        Doctor::Diagnose("Buffer overflow!");
                        goto Failure;
                    }
                    $ Advance();
                } while ($ peek == '0' || $ peek == '1' || $ peek == '_');
                buffer.Put(0);
                if (Text8::ToNatural(&token->Value.Machine, buffer.GetData()))
                    goto Epilogue;
                Doctor::Diagnose("Failed to convert binary literal.");
                goto Failure;
            case 'x': case 'X':
                $ Advance();
                token->Kind = Token::MACHINE;
                if (!Text8::IsNumeric($ peek) || !($ peek >= 'A' && $ peek <= 'F') || !($ peek >= 'a' && $ peek <= 'f')) {
                    Doctor::Diagnose("Hexadecimal literal has the wrong format.");
                    goto Failure;
                } do {
                    if (!buffer.Put($ peek)) {
                        Doctor::Diagnose("Buffer overflow!");
                        goto Failure;
                    }
                    $ Advance();
                } while (Text8::IsNumeric($ peek) || ($ peek >= 'A' && $ peek <= 'F') || ($ peek >= 'a' && $ peek <= 'f'));
                buffer.Put(0);
                if (Text8::ToNatural(&token->Value.Machine, buffer.GetData()))
                    goto Epilogue;
                Doctor::Diagnose("Failed to convert binary literal.");
                goto Failure;
            default:
                break;
            }
        }

        if (Text8::IsNumeric($ peek) || $ peek == '_')
            $ LexNatural(&buffer, token);
        else if ($ peek == '.') {
            buffer.Put($ peek);
            $ LexNatural(&buffer, token);
        }
        token->Kind = Token::NATURAL;
        token->Value.Natural = 0;
        goto Epilogue;
    } else {
        switch ($ peek) {
        case '\\':
            switch ($ Peek(2)) {
            case '\\':
                token->Kind = Token::COMMENT;
                do $ Advance();
                while ($ peek != '\n' && $ peek != '\0');
                goto Single;
            case '*':
                token->Kind = Token::COMMENT;
                do $ Advance();
                while ($ peek != '*' && $ Peek(2) != '\\' || $ peek != '\0');
                if ($ peek == '\0')
                    goto Single;
                goto Double;
            default:
                break;
            }
        case '-':
            if ($ Peek(2) == '>') {
                token->Kind = Token::RIGHT_ARROW;
                goto Double;
            }
        case ':':
            if ($ Peek(2) == ':') {
                token->Kind = Token::DOUBLE_COLON;
                goto Double;
            }
        case '(':case ')':case '{':case '}':
        case ',':case ';':case '@':case '?':
        case '=':case '+':
            token->Kind = (Token::Id) $ peek;
            goto Single;
        default:
            result = Result::FAILURE;
            Doctor::Diagnose("Unknown token.");
            goto Single;
        }
    Double:
        $ Advance();
    Single:
        $ Advance();
        goto Epilogue;
    }

Failure:
    result = Result::FAILURE;

Epilogue:
    token->End = {
        .Row = $ point.Row,
        .Column = $ point.Column,
    };
    return result;

}
