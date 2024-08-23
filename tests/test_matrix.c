#include <assert.h>
#include <stdlib.h>
#include "../src/matrix.h"


void test_matrix_init_zeroes(void) {
    int rows = 600;
    int cols = 100;
    int **matrix_i;
    double **matrix_d;

    // Test: Initialize an integer matrix with zeroes and verify its elements
    // This tests whether `matrix_init_zeroes_i` initializes and returns a matrix
    // with all elements set to 0 (integer).
    matrix_i = matrix_init_zeroes_i(rows, cols);
    if (matrix_i == NULL) {
        printf("test_matrix.c :: test_matrix_init_zeroes :: FAILED 👎 <- failed to "
               "initialize test int zero matrix.\n");
        return;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix_i[i][j] != 0.0) {
                printf("test_matrix.c :: test_matrix_init_zeroes :: FAILED 👎 <- "
                       "element (%d, %d) of int zero matrix is not 0", i, j);
            }
        }
    }

    // Test: Initialize a double matrix with zeroes and verify its elements
    // This tests whether `matrix_init_zeroes_d` initializes and returns a matrix
    // with all elements set to 0.0 (double).
    matrix_d = matrix_init_zeroes_d(rows, cols);
    if (matrix_d == NULL) {
        printf("test_matrix.c :: test_matrix_init_zeroes :: FAILED 👎 <- failed to "
               "initialize test zero matrix.\n");
        return;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix_d[i][j] != 0.0) {
                printf("test_matrix.c :: test_matrix_init_zeroes_d :: FAILED 👎 <- "
                       "element (%d, %d) of double zero matrix is not 0.0", i, j);
            }
        }
    }

    matrix_free((void **)matrix_i, rows);
    matrix_free((void **)matrix_d, rows);
    printf("test_matrix.c :: test_matrix_init_zeroes_d :: PASSED 👍\n");
}


void test_matrix_init_drand() {
    int rows = 600;
    int cols = 100;
    double min = 12.0;
    double max = 5234.0;

    // Test 1: Initialize a matrix with pseudo-random double values within the
    // range [min, max]
    double **matrix_a = matrix_init_drand(rows, cols, min, max);
    if (matrix_a == NULL) {
        printf("test_matrix.c :: test_matrix_init_randf :: FAILED 👎 <- failed "
               "matrix_init_drand on matrix_a.\n");
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix_a[i][j] <= min && matrix_a[i][j] >= max) {
                printf("test_matrix.c :: test_matrix_init_randf :: FAILED 👎 <- matrix_a's "
                        "elements are not within the specified range."
                       );
            }
        }
    }

    // Test 2: Ensure that matrix initialization fails when min > max
    double **matrix_b = matrix_init_drand(rows, cols, max, min);
    if (matrix_b != NULL) {
        printf("test_matrix.c :: test_matrix_init_randf :: FAILED 👎 <- "
               "matrix_init_drandf should fail if range of values is invalid.\n");
    }

    matrix_free((void **)matrix_a, rows);
    if (matrix_b != NULL) matrix_free((void **)matrix_a, rows);

    printf("test_matrix.c :: test_matrix_init_randf :: PASSED 👍\n");
}

int test_matrix(void) {
    test_matrix_init_zeroes();
    test_matrix_init_drand();
    printf("test_matrix.c :: test_matrix :: All tests passed 👍\n");
    return 0;
}
