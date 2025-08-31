cmake_minimum_required(VERSION 3.31)
project(hash_table)

set(CMAKE_CXX_STANDARD 23)

add_executable(hash_table main.cpp
        HashTable.h)

target_link_libraries(${PROJECT_NAME} PRIVATE stdc++exp)
