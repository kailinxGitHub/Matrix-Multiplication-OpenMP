#include <stdio.h>
#include <omp.h>
#include <time.h>

#define POWER 2
const int dim = (1 << POWER);

/**
 * Used to generate the matrices given numeric constraints.
 * @param lower the lower boundary for the generated int
 * @param upper the upper boundary for the generated int
 * @param matrix pointer to the matrix
 */
void randomIntGeneratorForMatrix(
        int lower,
        int upper,
        int matrix[dim][dim]
        ) {
    for (int row = 0; row < dim; row++) {
        for (int col = 0; col < dim; col++) {
            matrix[row][col] = rand() % (upper - lower + 1) + lower;
        }
    }
}

/**
 * Prints the matrix.
 * @param matrix pointer to the matrix
 */
void printMatrix(
        int matrix[dim][dim]
        ) {
    printf("Matrix: \n");
    for (int row = 0; row < dim; row++) {
        for (int col = 0; col < dim; col++) {
            printf("%d ", matrix[row][col]);
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL));

    int matrix_one[dim][dim];
    int matrix_two[dim][dim];
    int result[dim][dim];

    printf("Hello from process: %d\n", omp_get_thread_num());
    randomIntGeneratorForMatrix(1,100,matrix_one);
    printMatrix(matrix_one);
    return 0;
}