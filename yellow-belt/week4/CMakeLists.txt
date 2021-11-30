cmake_minimum_required(VERSION 3.20)
project(week4)

set(CMAKE_CXX_STANDARD 17)

add_executable(week4 main.cpp "iterators intro/print_vector_part.cpp" "iterators intro/find_greater_element.cpp" "iterators intro/split.cpp" "iterators usage/remove_duplicates.cpp" "iterators usage/get_perms_reversed.cpp" "iterators usage/demography_stat.cpp" "iterators usage/merge_sort.cpp")
