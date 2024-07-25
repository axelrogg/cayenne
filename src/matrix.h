#ifndef MATRIX_H
#define MATRIX_H

#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#define MAX_BUFFER_SIZE 500

int mat_init(float **A, int rows, int cols);
int mat_init_randf(float **matrix, int rows, int cols ,float *min, float *max);
void mat_print(int **matrix, int num_rows, int num_cols);
void mat_free(float **matrix, int num_rows);

#endif // !MATRIX_H
