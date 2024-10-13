#include <stdio.h>
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
 */
double OmpMatrixMultiplication(
        int matrix_one[dim][dim],
        int matrix_two[dim][dim],
        int result_matrix[dim][dim]
        ) {
    double start, end;

    start = omp_get_wtime();
    #pragma omp parallel for num_threads(10) schedule(static) shared(matrix_one, matrix_two, result_matrix)
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

int main() {
    srand(time(NULL));

    int matrix_one[dim][dim];
    int matrix_two[dim][dim];
    int result_matrix[dim][dim];

    RandomIntGeneratorForMatrix(1,100,matrix_one);
    RandomIntGeneratorForMatrix(1,100,matrix_two);
    double smm = StandardMatrixMultiplication(matrix_one, matrix_two, result_matrix);
//    PrintMatrix(matrix_one);
//    PrintMatrix(matrix_two);
//    PrintMatrix(result_matrix);
    printf("---\n");
    double omm = OmpMatrixMultiplication(matrix_one, matrix_two, result_matrix);
//    PrintMatrix(matrix_one);
//    PrintMatrix(matrix_two);
//    PrintMatrix(result_matrix);
    printf("---\n");
    printf("Time difference between Standard and OpenMP matrix multiplication: %f times faster.", (double)(smm / omm));
    return 0;
}