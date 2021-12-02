cmake_minimum_required(VERSION 3.20)
project(week6)

set(CMAKE_CXX_STANDARD 17)

add_executable(week6 main.cpp token.h token.cpp condition_parser.h condition_parser.cpp condition_parser_test.cpp date.cpp date.h database.cpp database.h)
