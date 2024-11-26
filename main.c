#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define POWER 9
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
 * @param result_matrix the result of the two matrices
 * @return time taken
 */
double StandardMatrixMultiplication(
        int matrix_one[dim][dim],
        int matrix_two[dim][dim],
        int result_matrix[dim][dim]
        ) {
    double start, end;

    start = omp_get_wtime();
    for (int row = 0; row < dim; row++) {
        for (int col = 0; col < dim; col++) {
            int sum = 0;
            for (int current_row_or_col = 0; current_row_or_col < dim; current_row_or_col++) {
                sum += matrix_one[row][current_row_or_col] * matrix_two[current_row_or_col][col];
            }
            result_matrix[row][col] = sum;
        }
    }
    end = omp_get_wtime();
    double time_taken = end - start;
    printf("Standard Matrix Multiplication took %.10f Seconds\n", time_taken);
    return time_taken;
}

/**
 * Function for matrix multiplication using openmp.
 * @param matrix_one the first matrix to be multiplied
 * @param matrix_two the second matrix to be multiplied
 * @param result_matrix the result of the two matrices
 * @param threads_limits the number of threads as a limit
 * @return time taken
 */
double OmpMatrixMultiplication(
        int matrix_one[512][512],
        int matrix_two[512][512],
        int result_matrix[512][512],
        int threads_limit
        ) {
    double start, end;

    start = omp_get_wtime();
    #pragma omp parallel for num_threads(threads_limit) schedule(static) shared(matrix_one, matrix_two, result_matrix)
    for (int row = 0; row < dim; row++) {
        for (int col = 0; col < dim; col++) {
            int sum = 0;
            for (int current_row_or_col = 0; current_row_or_col < dim; current_row_or_col++) {
                sum += matrix_one[row][current_row_or_col] * matrix_two[current_row_or_col][col];
            }
            result_matrix[row][col] = sum;
        }
    }
    end = omp_get_wtime();
    double time_taken = end - start;
    printf("OpenMP Matrix Multiplication took %.10f Seconds\n", time_taken);
    return time_taken;
}

/**
 * Function that uses loop tiling for the standard matrix multiplication.
 * @param matrix_one the first matrix to be multiplied
 * @param matrix_two the second matrix to be multiplied
 * @param result_matrix the result of the two matrices
 * @return time taken
 */
double StandardTilingMatrixMultiplication(
        int matrix_one[dim][dim],
        int matrix_two[dim][dim],
        int result_matrix[dim][dim]
) {
    double start, end;
    int tile_size = 2;

    start = omp_get_wtime();
    for (int row = 0; row < dim; row++) {
        for (int col = 0; col < dim; col++) {
            int sum = 0;
            for (int current_row_or_col = 0; current_row_or_col < dim; current_row_or_col++) {
                sum += matrix_one[row][current_row_or_col] * matrix_two[current_row_or_col][col];
            }
            result_matrix[row][col] = sum;
        }
    }
    end = omp_get_wtime();
    double time_taken = end - start;
    printf("Standard Matrix Multiplication took %.10f Seconds\n", time_taken);
    return time_taken;
}

int main() {
    srand(time(NULL));

    int matrix_one[dim][dim];
    int matrix_two[dim][dim];
    int result_matrix[dim][dim];

    RandomIntGeneratorForMatrix(1,100,matrix_one);
    RandomIntGeneratorForMatrix(1,100,matrix_two);

    int threads_limits[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int i = 0; i < 10; i++) {
        printf("For a thread limit of %i: ", threads_limits[i]);
        double smm = StandardMatrixMultiplication(matrix_one, matrix_two, result_matrix);
//    PrintMatrix(matrix_one);
//    PrintMatrix(matrix_two);
//    PrintMatrix(result_matrix);
        double omm = OmpMatrixMultiplication(matrix_one, matrix_two, result_matrix, 0);
//    PrintMatrix(matrix_one);
//    PrintMatrix(matrix_two);
//    PrintMatrix(result_matrix);
        printf("Time difference between Standard and OpenMP matrix multiplication: %f times faster.", (double)(smm / omm));
        printf("\n---\n");
    }
    return 0;
}