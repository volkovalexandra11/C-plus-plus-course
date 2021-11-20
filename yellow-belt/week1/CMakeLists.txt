cmake_minimum_required(VERSION 3.20)
project(week1)

set(CMAKE_CXX_STANDARD 17)

add_executable(week1 main.cpp matrix_task/matrix.cpp matrix_task/matrix.h "integral types/average_temperature_task.cpp" "integral types/parallelepiped.cpp" "tuples and pairs/regions_base.cpp" "tuples and pairs/TeamTasks.cpp" "tuples and pairs/TeamTasks.h" templates/sqr.cpp)
