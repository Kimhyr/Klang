// #include <fstream>
// #include <iostream>

// #include "Analyzer/Lexer.hpp"

// Int32 Initiate(const Int32 argc, const Char8 **argv) {
//   if (argc <= 1) {
//     return 1;
//   }

//   ErrorBuffer errBuf;
//   String buffer;
//   std::fstream file;
//   file.open(argv[1]);
//   if (!file.is_open()) {
//     return 1;
//   }

//   Char8 chr;
//   while ((chr = file.get()) != EOF) {
//     buffer.Put(chr);
//     std::cout << chr;
//   }
//   const Char8 *source = buffer.Flush();
//   buffer.Destroy();
//   Lexer lexer(&errBuf, "penis", source);
//   std::cout << '\n';
//   Lexer::Flag flags;
//   Token token;
//   do {
//     flags = lexer.Lex(&token);
//     std::cout << token.KindToStr() << '\t';
//     std::cout << token.start.row << ':' << token.start.column << ' ';
//     std::cout << token.end.row << ':' << token.end.column << '\n';
//   } while (!Lexer::FlagHasEoF(flags));
//   delete source;
//   lexer.Destroy();
//   return 0;
// }
