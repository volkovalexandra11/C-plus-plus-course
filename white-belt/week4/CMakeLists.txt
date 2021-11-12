cmake_minimum_required(VERSION 3.20)
project(week4)

set(CMAKE_CXX_STANDARD 17)

add_executable(week4 main.cpp LectureTitle.cpp LectureTitle.h Function.cpp Function.h InvertFunction.cpp exceptions/exceptions.cpp exceptions/TimeServer.cpp exceptions/TimeServer.h)
