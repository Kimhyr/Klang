#include "Lexer.H"

#include "../Utilities/Buffer.H"
#include "../Doctor.H"

Void Lexer::Destroy() {
    delete[] $ source;
}

Result Lexer::Lex(Token *token) {
    while (U::Text8::IsWhitespace($ peek))
        $ Advance();
    token->Start = $ point;
    if ($ peek == '\0') {
        token->ID = TokenID::END;
        goto Epilogue;
    }

    if (U::Text8::IsAlphabetic($ peek) || $ peek == '_') {
        U::Buffer<Sym8, Lexer::MAX_IDENTIFIER_LENGTH> buffer;
        do {
            if (!buffer.Put($ peek)) {
                Doctor::Diagnose("Buffer overflow!");
                goto Failure;
            }
            $ Advance();
        } while (U::Text8::IsNumeric($ peek) || U::Text8::IsAlphabetic($ peek) || $ peek == '_');
        buffer.Put('\0');
        TokenID keyword;
        if (Lexer::KEYWORD_TABLE.Get(buffer.GetData(), &keyword) == Result::SUCCESS)
            token->ID = keyword;
        else {
            token->ID = TokenID::IDENTIFIER;
            token->Value.Identifier = buffer.Flush();
        }
    } else if (U::Text8::IsNumeric($ peek)) {
        U::Buffer<Sym8, Lexer::MAX_NUMBER_LENGTH> buffer;
        if ($ peek == '0') {
            $ Advance();
            switch ($ peek) {
            case '0':
                do $ Advance();
                while ($ peek == '0');
                break;
            case 'b': case 'B':
                $ Advance();
                // TODO: Lex binary.
                goto Epilogue;
            case 'x': case 'X':
                $ Advance();
                // TODO: Lex hexadecimal
                goto Epilogue;
            default:
                break;
            }
        }

        if ("Is valid natural symbol")
            $ LexNatural(&buffer, token);
        else if ($ peek == '.') {
            buffer.Put($ peek);
            $ LexNatural(&buffer, token);
        }
        token->ID = TokenID::NATURAL;
        token->Value.Natural = 0;
    } else {

    }

Epilogue:
    token->End = {
        .Row = $ point.Row,
        .Column = $ point.Column,
    };
    return Result::SUCCESS;

Failure:
    return Result::FAILURE;
}
