CMAKE_MINIMUM_REQUIRED(VERSION 3.23)

SET(CMAKE_CXX_STANDARD 20)

PROJECT(KPLC)

ADD_COMPILE_OPTIONS(-Wall -Wextra -Werror)

FILE(GLOB SOURCES
        ./Source/*.hpp
        ./Source/*.cpp
        ./Source/Compiler/*.hpp
        ./Source/Compiler/*.cpp
        ./Source/Utility/*.hpp
        ./Source/Utility/*.cpp
        ./Source/Compiler/Analyzer/*.hpp
        ./Source/Compiler/Analyzer/*.cpp
        ./Source/Utility/Collections/*.hpp
        ./Source/Utility/Collections/*.cpp
        ./Source/Utility/Exceptions/*.hpp
        ./Source/Utility/Exceptions/*.cpp
        ./Source/Utility/System/*.hpp
        ./Source/Utility/System/*.cpp
        ./Source/Utility/Text/*.hpp
        ./Source/Utility/Text/*.cpp
)

ADD_EXECUTABLE(KPLC ${SOURCES})
