#ifndef LINALG_H

double **linalg_matmul(
    double **matrix_a,
    double **matrix_b,
    int rows_a,
    int cols_a,
    int rows_b,
    int cols_b
);

int linalg_luf(double **matrix, int n, double **matrix_lu);

double linalg_det(double **matrix, int n);

int linalg_solve(double **matrix, int n, double *b, double *x);

#endif // !LINALG_H
