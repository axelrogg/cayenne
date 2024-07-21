#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include "../src/matrix.h"


void test_luf() {
    float **A = malloc(4 * sizeof(float*));
    float **F = malloc(4 * sizeof(float*));
    float **L = malloc(4 * sizeof(float*));
    float **U = malloc(4 * sizeof(float*));

    float matrixA_vals[4][4] = {
        {2.0, 1.0, 3.0, 4.0},
        {8.0, 7.0, 4.0, 3.0},
        {4.0, 5.0, 1.0, 2.0},
        {1.0, 3.0, 4.0, 5.0}
    };
    for (int i = 0; i < 4; i++) {
        A[i] = malloc(4 * sizeof(float));
        for (int j = 0; j < 4; j++) {
            A[i][j] = matrixA_vals[i][j];
        }
    }
    for (int i = 0; i < 4; i++) {
        F[i] = malloc(4 * sizeof(float));
        for (int j = 0; j < 4; j++) {
            F[i][j] = 0.0;
        }
    }

    mat_luf(A, 4, F);
    for (int i = 0; i < 4; i++) {
        L[i] = malloc(4 * sizeof(float));
        U[i] = malloc(4 * sizeof(float));
        for (int j = 0; j < 4; j++) {
            L[i][j] = 0;
            if (i >= j) {
                L[i][j] = F[i][j];
                if (i == j) {
                    U[i][j] = 1.0;
                }
            } else {
                U[i][j] = F[i][j];
            }
        }
    }
    float **A_prime = mat_matmul(L, U, 4, 4, 4);
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++) {
            assert(fabs((A[i][j] - A_prime[i][j]) / A[i][j]) <= 0.001);
        }
    }
    printf("test_matrix.c :: test_luf :: PASSED\n");
}

int test_matrix() {
    test_luf();
    printf("test_matrix.c :: All tests passed.\n");
    return 0;
}
