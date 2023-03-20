cmake_minimum_required(VERSION 3.0.0)
project(Klang VERSION 0.1.0)

#### Random Shit ##############################################################
set(EXECUTABLE_OUTPUT_PATH "./")
set(CMAKE_BUILD_TYPE "Debug")

include_directories(./Source)

#### CMAKE_CXX Settings #######################################################
set(CMAKE_CXX_FLAGS "/O2 /Wall /std:c++latest ${CMAKE_CXX_FLAGS}")

#### Klang Executable #########################################################
file(GLOB_RECURSE KLANG_SOURCES ./Source/*.cpp ./Source/*.hpp)
add_executable(Klang ${KLANG_SOURCES})
target_include_directories(Klang PRIVATE ./Source)
