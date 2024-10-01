cmake_minimum_required(VERSION 3.29)
project(Matrix_Multiplication_OpenMP)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_C_COMPILER "/opt/homebrew/bin/gcc-14")
set(CMAKE_CXX_COMPILER "/opt/homebrew/bin/g++-14")

add_executable(Matrix_Multiplication_OpenMP
        main.cpp)