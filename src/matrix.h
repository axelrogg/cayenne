#ifndef MATRIX_H
#define MATRIX_H

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define MAX_BUFFER_SIZE 500

int **matrix_init_zeroes_i(int rows, int cols);
double **matrix_init_zeroes_d(int rows, int cols);
double **matrix_init_drand(int rows, int cols, double min, double max);
int matrix_dfill(double **matrix, int rows, int cols,
                 double values[rows][cols]);
void matrix_print(int **matrix, int num_rows, int num_cols);
void matrix_free(void **matrix, int num_rows);

#endif // !MATRIX_H
