cmake_minimum_required(VERSION 3.20)
project(week3)

set(CMAKE_CXX_STANDARD 17)

add_executable(week3 main.cpp "multi-file projects/sum_reverse_sort.h" "multi-file projects/sum_reverse_sort.cpp"
        "multi-file projects/PhoneNumber.cpp" "multi-file projects/phone_number.h")
