cmake_minimum_required(VERSION 3.19)
project(Java_Compiler_Phase2)

set(CMAKE_CXX_STANDARD 14)

include_directories(def)

add_executable(Java_Compiler_Phase2
        def/ParsingTableBuilder.h
        src/ParsingTableBuilder.cpp
        userInterface/File.h
        userInterface/File.cpp
        main.cpp)
