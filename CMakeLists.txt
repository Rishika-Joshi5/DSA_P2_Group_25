cmake_minimum_required(VERSION 4.1)
project(DSA_P2_Group_25)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(DSA_P2_Group_25
        src/main.cpp
        src/tree.cpp
        src/tree.h
        src/food.h
        src/food.cpp
        src/reader.h
        src/reader.cpp)
