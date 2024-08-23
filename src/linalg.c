#include "matrix.h"
#include "vector.h"
#include <math.h>
#include <stdlib.h>

double **linalg_matmul(
    double **matrix_a,
    double **matrix_b,
    int rows_a,
    int cols_a,
    int rows_b,
    int cols_b
) {

    if (cols_a != rows_b) {
        printf("linalg.c :: matmul :: number of columns of matrix A do not match the number of rows of matrix B\n");
        return NULL;
    }

    double **matrix_result = malloc(rows_a * sizeof(double *));
    if (matrix_result == NULL) {
        printf(
            "linalg.c :: matmul :: cannot allocate memory for matrix_result\n");
        return NULL;
    }

    for (int i = 0; i < rows_a; i++) {
        matrix_result[i] = malloc(cols_b * sizeof(double));
        if (matrix_result[i] == NULL) {
            // If we're here, free the matrix up to that point (up to row `i`)
            matrix_free((void **)matrix_result, i);
            printf("linalg.c :: matmul :: cannot allocate memory to row %d of matrix_result\n", i);
            return NULL;
        }
        for (int j = 0; j < cols_b; j++) {
            double sum = 0;
            for (int k = 0; k < rows_b; k++) {
                sum += matrix_a[i][k] * matrix_b[k][j];
            }
            matrix_result[i][j] = sum;
        }
    }
    return matrix_result;
}

int linalg_luf(double **matrix, int n, double **matrix_lu) {
    if (matrix == NULL) {
        printf("linalg.c :: lufactor :: matrix is NULL.\n");
        return -1;
    }

    if (n <= 0) {
        printf("linalg.c :: lufactor :: size n of matrix cannot be less than or equal to 0.\n");
        return -1;
    }

    if (matrix_lu == NULL) {
        printf("linalg.c :: lufactor :: matrix_lu is NULL.\n");
        return -1;
    }

    // Perform LU factorization of `matrix` into `matrix_lu`. Notice that
    // `matrix_lu` contains information about L and U. In fact,
    // `matrix_lu` = L + U - I, where I is the n x n identity matrix.
    for (int k = 0; k < n; k++) {
        // This sets the values of matrix L into `matrix_lu`.
        // We move downward within a given column. Remember that L is a lower
        // triangular, and the values of the elements in its diagonal are not
        // necessarily 1s.
        for (int i = k; i < n; i++) {
            double sum = 0;
            for (int t = 0; t < k; t++) {
                sum += matrix_lu[i][t] * matrix_lu[t][k];
            }
            matrix_lu[i][k] = matrix[i][k] - sum;
        }
        // This sets the values of matrix U into `matrix_lu` (with a
        // modification). The modification is as follows. In Crout's algorithm,
        // we establish that the elements of the diagonal of U are all 1s.
        // However, since we want all the information of L and U to be in a
        // single matrix LUI, we cannot satisfy that requirement (the diagonal
        // of `matrix_lu` at this point is filled with values that belong to L).
        // Instead, we don't bother assigning values to the diagonal of U (we
        // already know what they are--they are all 1s). This is what makes
        // `matrix_lu` = L + U - I.
        for (int j = k + 1; j < n; j++) {
            double sum = 0;
            for (int t = 0; t < k; t++) {
                sum += matrix_lu[k][t] * matrix_lu[t][j];
            }
            matrix_lu[k][j] = (matrix[k][j] - sum) / matrix_lu[k][k];
        }
    }
    return 0;
}

double linalg_det(double **matrix, int n) {
    if (matrix == NULL) {
        printf("linalg.c :: linalg_det :: matrix is NULL.\n");
        return NAN;
    }

    double **matrix_lu = matrix_init_zeroes_d(n, n);
    if (matrix_lu == NULL) {
        printf("linalg.c :: linalg_det :: matrix_lu wasn't initialized.\n");
        return NAN;
    }

    if (linalg_luf(matrix, n, matrix_lu) == -1) {
        matrix_free((void **)matrix_lu, n);
        printf("linalg.c :: linal_det :: LU factorization failed.\n");
        return NAN;
    }

    double det = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                det *= matrix_lu[i][j];
            }
        }
    }
    matrix_free((void **)matrix_lu, n);
    return det;
}

int linalg_solve(double **matrix, int n, double *b, double *x) {
    if (matrix == NULL) {
        printf("linalg.c :: linalg_lineq_solve :: matrix is NULL.\n");
    }
    if (b == NULL) {
        printf("linalg.c :: linalg_lineq_solve :: vector b is NULL.\n");
        return -1;
    }
    if (x == NULL) {
        printf("linalg.c :: linalg_lineq_solve :: vector x is NULL.\n");
        return -1;
    }

    if (n <= 0) {
        printf("linalg.c :: linalg_lineq_solve :: size n of matrix cannot be less than or equal to 0.\n");
        return -1;
    }

    double **matrix_lu = matrix_init_zeroes_d(n, n);
    if (matrix_lu == NULL) {
        printf("linalg.c :: linalg_lineq_solve :: matrix_lu wasn't initialized.\n");
        return -1;
    }

    if (linalg_luf(matrix, n, matrix_lu) == -1) {
        matrix_free((void **)matrix_lu, n);
        printf("linalg.c :: linalg_lineq_solve :: LU factorization failed.\n");
    }

    // Perform forward substitution.
    // We solve the equation Ly = b, where `b` is the argument passed into the
    // function.
    double *y = vector_init_zeroes_d(n);
    if (y == NULL) {
        matrix_free((void **)matrix_lu, n);
        printf("linalg.c :: linalg_lineq_solve :: could not allocate memory to create float array y.\n");
        return -1;
    }
    for (int j = 0; j < n; j++) {
        double sum = 0;
        for (int k = 0; k < j; k++) {
            sum += matrix_lu[j][k] * y[k];
        }
        y[j] = (b[j] - sum) / matrix_lu[j][j];
    }

    // Perform backward substitution.
    // We solve the equation Ux = y, where `y` is the vector found in the
    // forward substitution process above.
    for (int j = n - 1; j >= 0; j--) {
        double sum = 0;
        for (int k = j + 1; k < n; k++) {
            sum += matrix_lu[j][k] * x[k];
        }
        // No division needed here because Crout's algorithm assumes that the
        // matrix U from `LUI` has 1s on its diagonal.
        x[j] = y[j] - sum;
    }
    matrix_free((void **)matrix_lu, n);
    free(y);
    return 0;
}
