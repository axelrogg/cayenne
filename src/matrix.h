#ifndef MATRIX_H
#define MATRIX_H

#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#define MAX_BUFFER_SIZE 500

void mat_print(int **matrix, int num_rows, int num_cols);
float** mat_matmul(float** A, float** B, int rows_numA, int cols_numA, int cols_numB);

/**
 * @brief Performs LU factorization on a given square matrix `A`
 *
 * This function takes a square nxn matrix `A` and computes its LU factorization,
 * storing the result in a nxn matrix `C`. `mat_lu_factor` uses Crout’s Algorithm
 * to determine L and U, where U is an upper triangular matrix with all the elements
 * on its diagonal equal to 1.
 *
 * It is important to note that the matrix `C` contains information about L and U at
 * the same time. In fact, C = L + U - I, where I is the identity matrix of size `n`.
 *
 * @param A: A pointer to the original matrix A to be factorized.
 * @param n: The dimension of the square matrix A (and C).
 * @param C: A pointer to the matrix C, where the result of the factorization will be
 *           stored. `C` must be pre-allocated and must be of dimensions nxn.
 *
 * @return:  Returns `0` if the factorization was successul, or -1 is there was an
 *           error (e.g., if `A` or `C` is `NULL`).
 *
 * @note:    The function does not check for singularity of matrix A. The caller must
 *           wnsure that `A` is non-singular and well-conditioned before using this
 *           function.
 */
int mat_luf(float** A, int n, float** C);
void mat_free(void** matrix, int num_rows);

#endif // !MATRIX_H
