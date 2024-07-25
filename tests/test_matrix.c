#include <assert.h>
#include <stdlib.h>
#include "../src/matrix.h"


void test_mat_init() {
    int rows = 600;
    int cols = 100;
    float **matrix = malloc(rows * sizeof(float*));
    if (matrix == NULL) {
        printf("test_matrix.c :: test_mat_init :: failed to allocate memory for test matrix.\n");
        printf("test_matrix.c :: test_mat_init :: FAILED 👎\n");
        return;
    }

    // Should return -1 if the matrix passed to the mat_init is NULL
    assert(mat_init(NULL, rows, cols) == -1);

    // Should return 0 if the matrix was successfully initiated.
    assert(mat_init(matrix, rows, cols) == 0);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            assert(matrix[i][j] == 0.0);
        }
    }
    printf("test_matrix.c :: test_mat_init :: PASSED 👍\n");
    mat_free(matrix, rows);
}


void test_mat_init_randf() {
    int rows = 600;
    int cols = 100;
    float min = 12.0;
    float max = 5234.0;
    float **matrix_a = malloc(rows * sizeof(float*));
    if (matrix_a == NULL) {
        printf("test_matrix.c :: test_mat_init_randf :: failed to allocate memory for test matrix matrix_a.\n");
        printf("test_matrix.c :: test_mat_init_randf :: FAILED 👎\n");
        return;
    }

    float **matrix_b = malloc(rows * sizeof(float*));
    if (matrix_b == NULL) {
        printf("test_matrix.c :: test_mat_init_randf :: failed to allocate memory for test matrix matrix_b.\n");
        printf("test_matrix.c :: test_mat_init_randf :: FAILED 👎\n");
        return;
    }

    float **matrix_c = malloc(rows * sizeof(float*));
    if (matrix_c == NULL) {
        printf("test_matrix.c :: test_mat_init_randf :: failed to allocate memory for test matrix matrix_c.\n");
        printf("test_matrix.c :: test_mat_init_randf :: FAILED 👎\n");
        return;
    }

    float **matrix_d = malloc(rows * sizeof(float*));
    if (matrix_d == NULL) {
        printf("test_matrix.c :: test_mat_init_randf :: failed to allocate memory for test matrix matrix_d.\n");
        printf("test_matrix.c :: test_mat_init_randf :: FAILED 👎\n");
        return;
    }


    mat_init_randf(matrix_a, rows, cols, &min, &max);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            assert(matrix_a[i][j] > min && matrix_a[i][j] < max);
        }
    }
    mat_free(matrix_a, rows);

    mat_init_randf(matrix_b, rows, cols, NULL, &max);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            assert(matrix_b[i][j] > 0 && matrix_b[i][j] < max);
        }
    }
    mat_free(matrix_b, rows);

    mat_init_randf(matrix_c, rows, cols, &min, NULL);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            assert(matrix_c[i][j] > min && matrix_c[i][j] < (float)RAND_MAX);
        }
    }
    mat_free(matrix_c, rows);

    mat_init_randf(matrix_d, rows, cols, NULL, NULL);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            assert(matrix_d[i][j] > 0 && matrix_d[i][j] < (float)RAND_MAX);
        }
    }
    mat_free(matrix_d, rows);
    printf("test_matrix.c :: test_mat_init_randf :: PASSED 👍\n");
}

int test_matrix() {
    test_mat_init();
    test_mat_init_randf();
    printf("test_matrix.c :: test_matrix :: All tests passed 👍\n");
    return 0;
}
