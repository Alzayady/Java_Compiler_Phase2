cmake_minimum_required(VERSION 3.15)
project(Java_Compiler_Phase2)

set(CMAKE_CXX_STANDARD 14)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -D_LOCAL")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

include_directories(.)
include_directories(def)
include_directories(src)
include_directories(userInterface)

add_executable(Java_Compiler_Phase2
        def/InputMatcher.h
        src/InputMatcher.cpp
        def/ParsingTableBuilder.h
        src/ParsingTableBuilder.cpp
        userInterface/File.cpp
        userInterface/File.h
        FirstAndFollowTester.h
        main.cpp)
