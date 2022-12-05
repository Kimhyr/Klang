CMAKE_MINIMUM_REQUIRED(VERSION 3.23)

SET(CMAKE_CXX_STANDARD 20)

PROJECT(KPLC)

ADD_COMPILE_OPTIONS(-Wall -Wextra -Werror)

FILE(GLOB SOURCES
        ./Source/*.hpp
        ./Source/*.cpp
        ./Source/Compiler/*.hpp
        ./Source/Compiler/*.cpp
        Source/Analyzer/*.hpp
        Source/Analyzer/*.cpp
        Source/_/*.hpp
        Source/_/*.cpp
        Source/_/Collections/*.hpp
        Source/_/Collections/*.cpp
        Source/_/Exceptions/*.hpp
        Source/_/Exceptions/*.cpp
        Source/_/System/*.hpp
        Source/_/System/*.cpp
        Source/_/Text/*.hpp
        Source/_/Text/*.cpp
)

ADD_EXECUTABLE(KPLC ${SOURCES})
