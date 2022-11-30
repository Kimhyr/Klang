CMAKE_MINIMUM_REQUIRED(VERSION 3.23)

ADD_COMPILE_OPTIONS(-Wall -Wextra -Werror)
SET(CMAKE_CXX_STANDARD 20)

PROJECT(Compiler)

ADD_EXECUTABLE(Compiler Main.cpp Compiler/Analyzer/Token.cpp Compiler/Analyzer/Token.hpp Definitions.hpp Collections/Dynar.cpp Collections/Dynar.hpp Compiler/Error.cpp Compiler/Error.hpp Compiler/Analyzer/Lexer.cpp Compiler/Analyzer/Lexer.hpp Text/Char.hpp Text/String.cpp Text/String.hpp System/Memory.cpp System/Memory.hpp Number/Integer.cpp Number/Integer.hpp)
