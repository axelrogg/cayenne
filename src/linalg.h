#ifndef LINALG_H


/**
 * @brief Performs matrix multiplication and stores the result into another matrix.
 *
 * This function multiplies `matrix_a` (`rows_a` x `cols_a`) by
 * `matrix_b` (`rows_b` x `cols_b`) and stores the result into `matrix_result`.
 * To be able to multiply `matrix_a` by `matrix_b` it is necessary that `cols_a`
 * and `rows_b` are of the same value. Otherwise, the function exists returning
 * `-1`.
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
           int   cols_b);


/**
 * @brief Solves a system of linear equations of the form Ax = b.
 *
 * This function takes a square `matrix` (`n` x `n`) and an array `b` and stores
 * the result of the system into the array `x`.
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
int lineq_solve(float** matrix, int n, float *b, float *x);

#endif // !LINALG_H
