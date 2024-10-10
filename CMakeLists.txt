cmake_minimum_required(VERSION 3.29)
set(CMAKE_C_COMPILER "/opt/homebrew/opt/llvm/bin/clang")
set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++")

project(Matrix_Multiplication_OpenMP C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Xclang -fopenmp -L/opt/homebrew/opt/libomp/lib -I/opt/homebrew/opt/libomp/include -lomp")

add_executable(Matrix_Multiplication_OpenMP main.c)