cmake_minimum_required(VERSION 3.23)

add_compile_options(-Wall -Wextra -Werror)
set(CMAKE_CXX_STANDARD 20)

project(Compiler)

add_executable(Compiler Main.cpp Analyzer/Token.cpp Analyzer/Token.hpp Definitions.hpp Utility/Dynar.cpp Utility/Dynar.hpp Utility/Error.cpp Utility/Error.hpp Module.hpp Analyzer/Lexer.cpp Analyzer/Lexer.hpp Utility/Char.hpp Utility/Text.cpp Utility/Text.hpp)
