CMAKE_MINIMUM_REQUIRED(VERSION 3.23)

ADD_COMPILE_OPTIONS(-Wall -Wextra -Werror)
SET(CMAKE_CXX_STANDARD 20)

PROJECT(Compiler)

ADD_EXECUTABLE(Compiler Main.cpp Analyzer/Token.cpp Analyzer/Token.hpp Definitions.hpp Utility/Dynar.cpp Utility/Dynar.hpp Utility/Error.cpp Utility/Error.hpp Module.hpp Analyzer/Lexer.cpp Analyzer/Lexer.hpp Utility/Char.hpp Utility/Text.cpp Utility/Text.hpp)
