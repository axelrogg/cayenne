#ifndef MATRIX_H
#define MATRIX_H

#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#define MAX_BUFFER_SIZE 500

void matrix_print(int **matrix, int num_rows, int num_cols);
float** mat_matmul(float** A, float** B, int rows_numA, int cols_numA, int cols_numB);
void mat_free(void** matrix, int num_rows);

#endif // !MATRIX_H
