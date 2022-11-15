#include "Lexer.hpp"

#include "../Utils/Char.hpp"
#include "Token.hpp"

Lexer::Lexer(ErrorBuffer *errBuf, const Char8 *sourcePath, const Char8 *source)
    : errBuf(errBuf)
    , sourcePath(sourcePath)
    , source(source) {
}

Void Lexer::Advance() {
  this->peek = this->Peek();
  if (this->peek == '\n') {
    ++this->point.row;
    this->point.column = 0;
  }
  ++this->point.column;
  ++this->index;
}

Lexer::Flag Lexer::LexIdentifier(IdentifierT *out) {
  UInt8 flags;
  return (Lexer::Flag)flags;
}

// Lexer::Flag Lexer::LexIdentifier(Token *lexer) {
//   UInt8 flags = 0;
//   do {
//     lexer->buffer.Put(lexer->peek);
//     lexer->Advance();
//   } while (Char::IsAlphabetic(lexer->peek) || Char::IsNumeric(lexer->peek) ||
//            lexer->peek == '_');
//   if (lexer->peek == '\0') {
//     flags |= (UInt8)Lexer::Flag::EoF;
//   }
//   this->identifier = lexer->buffer.Flush();
//   return (Lexer::Flag)flags;
// }

// // TODO
// Lexer::Flag LiteralT::Lex(Lexer *lexer) {
//   UInt8 flags = 0;
//   switch (this->kind) {
//   case LiteralT::Kind::Void:
//     break;
//   case LiteralT::Kind::Integer:
//     do {
//       lexer->buffer.Put(lexer->peek);
//       lexer->Advance();
//     } while (Char::IsNumeric(lexer->peek) || lexer->peek == '_');
//     if (lexer->peek != '.') {
//       if (lexer->peek == '\0') {
//         flags |= (UInt8)Lexer::Flag::EoF;
//       }
//       goto END;
//     }
//     this->kind = LiteralT::Kind::Float;
//   case LiteralT::Kind::Float:
//     do {
//       lexer->buffer.Put(lexer->peek);
//       lexer->Advance();
//     } while (Char::IsNumeric(lexer->peek) || lexer->peek == '_');
//     if (lexer->peek == '.') {
//       flags |= (UInt8)Lexer::Flag::Error;
//       lexer->errBuf->Put(Error(
//           Error::Severity::Critical,
//           "This float literal token has too many dots."
//       ));
//     }
//     if (lexer->peek == '\0') {
//       flags |= (UInt8)Lexer::Flag::EoF;
//     }
//     goto END;
//   case LiteralT::Kind::Character:
//     break;
//   case LiteralT::Kind::String:
//     break;
//   }
// END:
//   return (Lexer::Flag)flags;
// }

// Lexer::Flag KeywordT::Lex(Lexer *lexer) {
//   UInt8 flags = 0;
//   Char8 *str = &lexer->buffer.buffer[lexer->index - 1];
//   if (lexer->peek == '\0') {
//     flags |= (UInt8)Lexer::Flag::EoF;
//   }
//   if (String::Compare(str, "procedure")) {
//     this->value = KeywordT::Value::Procedure;
//   } else if (String::Compare(str, "datum")) {
//     this->value = KeywordT::Value::Datum;
//   } else if (String::Compare(str, "return")) {
//     this->value = KeywordT::Value::Return;
//   } else {
//     flags |= (UInt8)Lexer::Flag::Switch;
//   }
//   return (Lexer::Flag)flags;
// }

// Lexer::Flag OperT::Lex(Lexer *lexer) {
//   UInt8 flags = 0;
//   if (lexer->peek == '\0') {
//     flags |= (UInt8)Lexer::Flag::EoF;
//   }
//   switch (lexer->peek) {
//   case '\0':
//     flags |= (UInt8)Lexer::Flag::EoF;
//     break;
//   default:
//     break;
//   }

//   return (Lexer::Flag)flags;
// }

// Lexer::Flag PunctuatorT::Lex(Lexer *lexer) {
//   UInt8 flags = 0;
//   if (lexer->peek == '\0') {
//     flags |= (UInt8)Lexer::Flag::EoF;
//   }
//   return (Lexer::Flag)flags;
// }

// Lexer::Flag ModifierT::Lex(Lexer *lexer) {
//   UInt8 flags = 0;
//   if (lexer->peek == '\0') {
//     flags |= (UInt8)Lexer::Flag::EoF;
//   }
//   return (Lexer::Flag)flags;
// }
