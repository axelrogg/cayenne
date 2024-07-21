#include <stdlib.h>
#include "matrix.h"

void mat_free(void** matrix, int num_rows) {
    if (matrix == NULL) {
        return;
    }
    for (int i = 0; i < num_rows; i++) {
        free(matrix[i]);
        matrix[i] = NULL;
    }
    free(matrix);
}

float** mat_matmul(float** A, float** B, int rows_numA, int cols_numA, int cols_numB) {
    float** result = malloc(rows_numA * sizeof(float*));
    for (int i = 0; i < rows_numA; i++) {
         result[i] = malloc(cols_numB * sizeof(float));
         for (int j = 0; j < cols_numB; j++) {
            float sum = 0;
            for (int k = 0; k < rows_numA; k++) {
                sum += A[i][k] * B[k][j];
            }
            result[i][j] = sum;
        }
    }
    return result;
}


/**
 * @brief Performs LU factorization on a given square matrix `A`
 *
 * This function takes a square nxn matrix `A` and computes its LU factorization,
 * storing the result in a nxn matrix `F`. `mat_luf` uses Crout’s Algorithm
 * to determine L and U, where U is an upper triangular matrix with all the elements
 * on its diagonal equal to 1.
 *
 * It is important to note that the matrix `F` contains information about L and U at
 * the same time. In fact, F = L + U - I, where I is the identity matrix of size `n`.
 *
 * @param A: A pointer to the original matrix A to be factorized.
 * @param n: The dimension of the square matrix A (and F).
 * @param F: A pointer to the matrix F, where the result of the factorization will be
 *           stored. `F` must be pre-allocated and must be of dimensions nxn.
 *
 * @return:  Returns `0` if the factorization was successul, or -1 is there was an
 *           error (e.g., if `A` or `F` is `NULL`, or if `n` is less than or
 *           equal to zero).
 *
 * @note:    The function does not check for singularity of matrix A. The caller must
 *           ensure that `A` is non-singular and well-conditioned before using this
 *           function.
 */
int mat_luf(float** A, int n, float** F) {
    if (A == NULL) {
        printf("mat_luf :: matrix A is NULL.");
        return -1;
    }
    if (F == NULL) {
        printf("mat_luf :: matrix F is NULL.");
        return -1;
    }
    if (n < 0) {
        printf("mat_luf :: size n of matrices cannot be less than or equal to 0.");
        return -1;
    }

    // Factorize A into F. Remember that F = L + U - I
    for (int k = 0; k < n; k++) {
        // Move downward within the same column (lower triangular).
        for (int i = k; i < n; i++) {
            float sum = 0;
            for (int t = 0; t < k; t++) {
                sum += F[i][t] * F[t][k];
            }
            F[i][k] = A[i][k] - sum;
        }
        // Move to the right within the same row.
        for (int j = k + 1; j < n; j++) {
            float sum = 0;
            for (int t = 0; t < k; t++) {
                sum += F[k][t] * F[t][j];
            }
            F[k][j] = (A[k][j] - sum) / F[k][k];
        }
    }

    return 0;
}


int to_buff(char *buff, size_t buff_size, int offset, const char *format, ...) {
    if (offset > 0 && (size_t)offset >= buff_size) {
        return -1;
    }

    va_list args;
    va_start(args, format);
    int num_chars = vsnprintf(buff + offset, buff_size - offset, format, args);
    va_end(args);

    if (num_chars < 0) {
        printf("to_buff :: An output error was encountered.\n");
        return -1;
    // `num_chars` is already greater than or equal to zero, so casting
    // it to a `size_t` is not a problem.
    } else if ((size_t)num_chars >= buff_size - offset) { 
        printf("to_buff :: Output was truncated.\n");
        return -1;
    }
    return num_chars;
}

int append_line_break(char *buff, size_t buff_size, int offset, int num_blocks) {
    int num_chars;
    int new_offset = 0;
    num_chars = to_buff(buff, buff_size, offset, "----");
    if (num_chars == -1) {
        return -1;
    }
    new_offset += num_chars;
    
    for (int i = 0; i < num_blocks; i++) {
        num_chars = to_buff(buff, buff_size, new_offset + offset, "+----");
        if (num_chars == -1) {
            return -1;
        }
        new_offset += num_chars;
    }

    // Add the newline character
    buff[new_offset++ + offset] = '\n';
    return new_offset;
}

void mat_print(int **matrix, int num_rows, int num_cols) {
    char buff[MAX_BUFFER_SIZE];
    int offset = 0;
    int num_chars;

    num_chars = to_buff(buff, MAX_BUFFER_SIZE, offset, "    ");
    if (num_chars == -1) {
        return;
    }
    offset += num_chars;
    
    for (int i = 0; i < num_cols; i++) {
        if (i < 10) {
            num_chars = to_buff(buff, MAX_BUFFER_SIZE, offset, "|  %d ", i);
        }
        else {
            num_chars = to_buff(buff, MAX_BUFFER_SIZE, offset, "| %d ", i);
        }
        if (num_chars == -1) {
            return;
        }
        offset += num_chars;
    }

    // Add the newline character
    buff[offset++] = '\n';
    offset += append_line_break(buff, 1000, offset, num_cols);

    for (int i = 0; i < num_rows; i++) {
        num_chars = to_buff(buff, MAX_BUFFER_SIZE, offset, "  %d ", i);
        if (num_chars == -1) {
            return;
        }
        offset += num_chars;

        for (int j = 0; j < num_cols; j++) {
            if (matrix[i][j] >= 0) {
                num_chars = to_buff(buff, MAX_BUFFER_SIZE, offset, "|  %d ", matrix[i][j]);
            }
            else {
                num_chars = to_buff(buff, MAX_BUFFER_SIZE, offset, "| %d ", matrix[i][j]);
            }
            if (num_chars == -1) {
                return;
            }
            offset += num_chars;
        }
        buff[offset++] = '\n';
        if (i < num_rows - 1) {
            offset += append_line_break(buff, 1000, offset, num_cols);
        }
    }

    // Add the newline character
    buff[offset++] = '\n';
    buff[offset] = '\0';

    printf("%s", buff);
}
