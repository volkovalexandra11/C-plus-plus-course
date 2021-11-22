cmake_minimum_required(VERSION 3.20)
project(week2)

set(CMAKE_CXX_STANDARD 17)

add_executable(week2 main.cpp "using unit tests/decomposition.cpp" "unit tests summary/RealRootsCountTests.cpp" "unit tests summary/PersonTests.cpp")
