project(Matrix_Multiplication_OpenMP C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Xclang -fopenmp -L/opt/homebrew/opt/libomp/lib -I/opt/homebrew/opt/libomp/include -lomp")

add_executable(Matrix_Multiplication_OpenMP main.c
)