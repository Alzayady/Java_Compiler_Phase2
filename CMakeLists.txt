cmake_minimum_required(VERSION 3.15)
project(Java_Compiler_Phase2)

set(CMAKE_CXX_STANDARD 14)



add_executable(Java_Compiler_Phase2
        def/InputMatcher.h
        def/ParsingTableBuilder.h
        src/InputMatcher.cpp
        src/ParsingTableBuilder.cpp
        userInterface/File.cpp
        userInterface/File.h
        FirstAndFollowTester.h
#        tests/InputMatcherTester.cpp
        main.cpp
        )
