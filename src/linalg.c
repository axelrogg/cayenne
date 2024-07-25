#include <stdlib.h>
#include "matrix.h"


/**
 * @brief Performs matrix multiplication and stores the result into another matrix.
 *
 * This function multiplies `matrix_a` (`rows_a` x `cols_a`) by
 * `matrix_b` (`rows_b` x `cols_b`) and stores the result into `matrix_result`.
 * To be able to multiply `matrix_a` by `matrix_b` it is necessary that `cols_a`
 * and `rows_b` are of the same value. Otherwise, the function exists returning
 * `-1`.
 *
 * We use a very naive implementation of matrix multiplication.
 *
 * @param matrix_a:      The first input matrix of dimension (`rows_a` x `cols_a`).
 * @param matrix_b:      The second input matrix of dimension (`rows_b` x `cols_b`).
 * @param matrix_result: This is where the result of the multiplication is stored.
 *                       Note that `matrix_result` does not need to be initialized
 *                       with `mat_init` before being passed into this function.
 * @param rows_a:        The number of rows in `matrix_a`.
 * @param cols_a:        The number of columns in `matrix_a`.
 * @param rows_b:        The number of rows in `matrix_b`. Must equal `cols_a`.
 * @param cols_b:        The number of columns in `matrix_b`.
 *
 * @return: Returns `0` on success and `-1` if `cols_a` is different than `rows_b`,
 *          or if memory allocation failed at some point.
 *
 * @note: The caller must ensure that `matrix_result` has enough space allocated
 *        for `rows_a` rows of pointers, and each of these pointers must be capable
 *        of pointing to an array of `cols_b` floats. This means that before
 *        `matrix_result` is passed into `matmul`, it is expected that the caller
 *        does:
 *
 *        float **matrix_result = malloc(rows_a * sizeof(float*));
 *
 *        This function takes care of the memory allocation of each row of
 *        `matrix_result`.
 */
int matmul(float **matrix_a,
           float **matrix_b,
           float **matrix_result,
           int   rows_a,
           int   cols_a,
           int   rows_b,
           int   cols_b) {

    if (cols_a != rows_b) {
        printf("linalg.c :: matmul :: number of columns of matrix A do not match the number of rows of matrix B\n");
        return -1;
    }

    for (int i = 0; i < rows_a; i++) {
        matrix_result[i] = malloc(cols_b * sizeof(float));
        if (matrix_result[i] == NULL) {
            // If we're here, free the matrix up to that point (up to row `i`)
            mat_free(matrix_result, i);
            printf("linalg.c :: matmul :: cannot allocate memory to row %d of matrix_result\n", i);
            return -1;
        }
         for (int j = 0; j < cols_b; j++) {
            float sum = 0;
            for (int k = 0; k < cols_b; k++) {
                sum += matrix_a[i][k] * matrix_b[k][j];
            }
            matrix_result[i][j] = sum;
        }
    }
    return 0;
}


/**
 * @brief Solves a system of linear equations of the form Ax = b.
 *
 * This function takes a square `matrix` (`n` x `n`) and an array `b` and stores
 * the result of the system into the array `x`. To solve the system, LU
 * factorization is used, relying on Crout's algorithm for the actual factorization
 * process. After that, foward and backward substitution are performed to finally
 * find the values of `x`.
 *
 * @param matrix: The input square coefficient matrix of size `n`.
 * @param n:      The dimension of `matrix`. Must be greater than 0 or the function
 *                returns -1.
 * @param b:      The array of constants on the right side of the equation Ax = b.
 * @param x:      The array where the solution of the linear system will be stored.
 *
 * @return: Returns 0 on success, or -1 on failure.
 *
 * @note: The caller must ensure that the arrays `b` and `x` have enough space
 *        allocated for `n` floats.
 */
int lineq_solve(float** matrix, int n, float *b, float *x) {
    float **LUI = malloc(n * sizeof(float*));
    if (LUI == NULL) {
        printf("linalg.c :: lineq_solve :: could not allocate memory to create matrix LUI.\n");
        return -1;
    }

    if (mat_init(LUI, n, n) == -1) {
        mat_free(LUI, n);
        printf("linalg.c :: lineq_solve :: matrix LUI wasn't initialized.\n");
        return -1;
    }

    if (matrix == NULL) {
        mat_free(LUI, n);
        printf("linalg.c :: lineq_solve :: matrix is NULL.\n");
        return -1;
    }

    if (n <= 0) {
        mat_free(LUI, n);
        printf("linalg.c :: lineq_solve :: size n of matrix cannot be less than or equal to 0.\n");
        return -1;
    }

    // Perform LU factorization of `matrix` into `LUI`. Notice that `LUI` contains
    // information about L and U. In fact, `LUI` = L + U - I, where I is the nxn
    // identity matrix.
    // This is a naive implementation of Crout's algorithm.
    for (int k = 0; k < n; k++) {
        // This sets the values of matrix L into `LUI`.
        // We move downward within a given column. Remember that L is a lower
        // triangular, and the values of the elements in its diagonal are not
        // necessarily 1s.
        for (int i = k; i < n; i++) {
            float sum = 0;
            for (int t = 0; t < k; t++) {
                sum += LUI[i][t] * LUI[t][k];
            }
            LUI[i][k] = matrix[i][k] - sum;
        }
        // This sets the values of matrix U into `LUI` (with a modification).
        // The modification is as follows. In Crout's algorithm, we establish
        // that the elements of the diagonal of U are all 1s. However, since
        // we want all the information of L and U to be in a single matrix LUI,
        // we cannot satisfy that requirement (the diagonal of `LUI` at this
        // point is filled with values that belong to L). Instead, we don't
        // bother assigning values to the diagonal of U (we already know what
        // they are--they are all 1s).
        // This is what makes `LUI` = L + U - I.
        for (int j = k + 1; j < n; j++) {
            float sum = 0;
            for (int t = 0; t < k; t++) {
                sum += LUI[k][t] * LUI[t][j];
            }
            LUI[k][j] = (matrix[k][j] - sum) / LUI[k][k];
        }
    }
    
    // Perform forward substitution.
    // We solve the equation Ly = b, where `b` is the argument passed into the
    // function.
    float *y = malloc(n * sizeof(float));
    if (y == NULL) {
        mat_free(LUI, n);
        printf(
            "linalg.c :: lineq_solve :: could not allocate memory to create float array y.\n"
        );
        return -1;
    }
    for (int i = 0; i < n; i++) {
        float sum = 0;
        for (int k = 0; k < i+1; k++) {
            sum += matrix[i][k] * y[k];
        }
        y[i] = (b[i] - sum) / matrix[i][i];
    }

    // Perform backward substitution.
    // We solve the equation Ux = y, where `y` is the vector found in the
    // forward substitution process above.
    for (int i = n - 1; i > n; i--) {
        float sum = 0;
        for (int k = i + 1; k < n; k++) {
            sum += matrix[i][k] * x[k];
        }
        // No division needed here because Crout's algorithm assumes that the
        // matrix U from `LUI` has 1s on its diagonal.
        x[i] = y[i] - sum;
    }
    mat_free(LUI, n);
    free(y);
    return 0;
}

