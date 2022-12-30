#include "lexer.hpp"

namespace KC {

Lexer::Lexer(const Sym *source)
        : cursor(source), point({.row = 1, .column = 1}) {}

Token Lexer::lex() {
        Token token(this->point);
        switch (*this->cursor) {
        case '0':
                token.tag = (Token::Tag)*this->cursor;
                this->advance();
                
                break;
        default:
                Buffer<Sym, Lexer::BUFFER_SIZE> buffer;
                if (this->isOnIdentifierSym()) {
                        token.tag = Token::Tag::IDENTIFIER;
                        this->lexIdentifier(&buffer);
                        goto Flush_Buffer;
                } else if (this->isOnDigitSym()) {
                        token.tag = Token::Tag::NATURAL;
                        do {
                                if (*this->cursor != '_')
                                        buffer.put(*this->cursor);
                                this->advance();
                        } while (this->isOnDigitSym() || *this->cursor == '_');
                        goto Flush_Buffer;
                //         try { buffer.put(*this->cursor); }
                //         catch (Result) { throw Diagnosis(); } 
                //         this->advance();
                //         if (this->cursor[-1] == '0') {
                //                 switch (*this->cursor) {
                //                 case 'B':
                //                 case 'b':
                //                         this->advance();
                //                         if (!this->isOnBinarySym())
                //                                 throw Diagnosis();
                //                         token.tag = Token::Tag::MACHINE;
                //                         this->lexBinary(&buffer);
                //                         goto Flush_Buffer;
                //                 case 'X':
                //                 case 'x':
                //                         this->advance();
                //                         if (!this->isOnHexadecimalSym())
                //                                 throw Diagnosis();
                //                         token.tag = Token::Tag::MACHINE;
                //                         this->lexHexadecimal(&buffer);
                //                         goto Flush_Buffer;
                //                 case '.':
                //                         token.tag = Token::Tag::REAL;
                //                         goto Lex_Natural;
                //                 default: break;
                //                 }
                //         }
                //         token.tag = Token::Tag::NATURAL;
                //         if (!this->isOnDigitSym())
                //                 goto Flush_Buffer;
                // Lex_Natural:
                //         this->lexNaturalAndReal(&buffer, &token);
                //         goto Flush_Buffer;
                }
                throw Diagnosis();
        Flush_Buffer:
                try { buffer.put(0); }
                catch (Result) { throw Diagnosis(); } 
                token.value = buffer.flush();
                break;
        }

// Epilogue:
        token.location.end = this->point;
        return token;
}

Void Lexer::advance() noexcept{
        if (*(++this->cursor) == '\n') {
                ++this->point.row;
                this->point.column = 0;
        }
        ++this->point.column;
}


Void Lexer::lexNaturalAndReal(Buffer<Sym, Lexer::BUFFER_SIZE> *buffer, Token *token) {
        do {
                switch (*this->cursor) {
                case '.':
                        if (token->tag == Token::Tag::REAL)
                                throw Diagnosis();
                        token->tag = Token::Tag::REAL;
                        break;
                case '_': goto Advance;
                }
                try { buffer->put(*this->cursor); }
                catch(Result) { throw Diagnosis(); }
        Advance:
                this->advance();
        } while (this->isOnDigitSym() || *this->cursor == '_');
}

Void Lexer::lexIdentifier(Buffer<Sym, Lexer::BUFFER_SIZE> *buffer) {
         do {
                try { buffer->put(*this->cursor); }
                catch (Result) { throw Diagnosis(); }
                this->advance();
        } while (this->isOnIdentifierSym());
}

Void Lexer::lexBinary(Buffer<Sym, Lexer::BUFFER_SIZE> *buffer) {
        do {
                if (*this->cursor != '_') {
                        try { buffer->put(*this->cursor); }
                        catch (Result) { throw Diagnosis(); }
                }
                this->advance();
        } while (this->isOnBinarySym() || *this->cursor == '_');
}

Void Lexer::lexHexadecimal(Buffer<Sym, Lexer::BUFFER_SIZE> *buffer) {
        do {
                if (*this->cursor != '_') {
                        try { buffer->put(*this->cursor); }
                        catch (Result) { throw Diagnosis(); }
                }
                this->advance();
        } while (this->isOnHexadecimalSym() || *this->cursor == '_');
}

} // namespace KC
