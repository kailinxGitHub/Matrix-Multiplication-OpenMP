#include <stdio.h>
#include <omp.h>
#include <time.h>

#define POWER 1
const int dim = (1 << POWER);

/**
 * Used to generate the matrices given numeric constraints.
 * @param lower the lower boundary for the generated int
 * @param upper the upper boundary for the generated int
 * @param matrix pointer to the matrix
 */
void RandomIntGeneratorForMatrix(
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
void PrintMatrix(
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

/**
 * The standard multiplication without omp.
 * @param matrix_one the first matrix to be multiplied
 * @param matrix_two the second matrix to be multiplied
 * @param result the result of the two matrices
 */
void StandardMatrixMultiplication(
        int matrix_one[dim][dim],
        int matrix_two[dim][dim],
        int result[dim][dim]
        ) {
    double start, end;

    start = clock();
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            int sum = 0;
            for (int k = 0; k < dim; k++) {
                sum += matrix_one[i][k] * matrix_two[k][j];
            }
            result[i][j] = sum;
        }
    }
    end = clock();
    double time_taken = (double)(end - start) / (double)(CLOCKS_PER_SEC);
    printf("Standard Matrix Multiplication took %.10f Seconds\n", time_taken);

}

int main() {
    srand(time(NULL));

    int matrix_one[dim][dim];
    int matrix_two[dim][dim];
    int result_matrix[dim][dim];

    RandomIntGeneratorForMatrix(1,100,matrix_one);
    RandomIntGeneratorForMatrix(1,100,matrix_two);
    StandardMatrixMultiplication(matrix_one, matrix_two, result_matrix);
    PrintMatrix(matrix_one);
    PrintMatrix(matrix_two);
    PrintMatrix(result_matrix);
    return 0;
}