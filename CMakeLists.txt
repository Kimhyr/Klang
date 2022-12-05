CMAKE_MINIMUM_REQUIRED(VERSION 3.23)

SET(CMAKE_CXX_STANDARD 20)

PROJECT(KPLC)

ADD_COMPILE_OPTIONS(-Wall -Wextra -Werror)

FILE(GLOB SOURCES
        ./Source/*.cpp
        ./Source/Compiler/*.cpp
        ./Source/Utilities/*.cpp
)

ADD_EXECUTABLE(KPLC ${SOURCES})
