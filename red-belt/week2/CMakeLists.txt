cmake_minimum_required(VERSION 3.20)
project(week2)

set(CMAKE_CXX_STANDARD 17)

add_executable(week2 main.cpp profile.h code_optimixation/students_compare.cpp code_optimixation/known_words.cpp complexity/express.cpp complexity/ebooks.cpp complexity/hotel_manager.cpp)
