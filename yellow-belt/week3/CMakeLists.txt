cmake_minimum_required(VERSION 3.20)
project(week3)

set(CMAKE_CXX_STANDARD 17)

add_executable(week3 main.cpp "multi-file projects/sum_reverse_sort.h" "multi-file projects/sum_reverse_sort.cpp"
        "multi-file projects/PhoneNumber.cpp" "multi-file projects/phone_number.h" "multi-file projects/Rectangle.cpp" "multi-file projects/rectangle.h" decomposition2/query.h decomposition2/query.cpp decomposition2/responses.h decomposition2/responses.cpp decomposition2/bus_manager.cpp decomposition2/bus_manager.h decomposition2/main.cpp)
