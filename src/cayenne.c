#include "digraph.h"
#include "matrix.h"
#include <stdio.h>

int test_incidence_matrix_total_rows_sum(int **matrix, int num_rows, int num_cols) {
    int total_rows_sum = 0;
    for (int i = 0; i < num_rows; i++) {
        int row_sum = 0;
        for (int j = 0; j < num_cols; j++) {
            row_sum += matrix[i][j];
        }
        total_rows_sum += row_sum;
    }
    if (total_rows_sum != 0) {
        printf("The element-wise sum of all the rows is %d but should be 0.\n", total_rows_sum);
        return -1;
    }
    return 0;
}

int test_incidence_matrix_col_sum(int **matrix, int num_rows, int num_cols) {
    for (int j = 0; j < num_cols; j++) {
        int col_value_sum = 0;
        for (int i = 0; i < num_rows; i++) {
            col_value_sum += matrix[i][j];
        }
        if (col_value_sum != 0) {
            printf("The sum of the elements in column %d is %d but should be 0.\n", j, col_value_sum);
            return -1;
        }
    }
    return 0;
}


int main() {
    // int num_vertices = 3;
    // int num_edges = 3;
    // int edges[3][2] = {
    //     {0, 1},
    //     {0, 2},
    //     {1, 2},
    // };
    // 
    // Digraph *digraph = digraph_build(num_vertices, num_edges, edges);
    // digraph_print(digraph);
    // printf("Number of edges: %d\n", digraph_num_edges(digraph));
    // int **incidence_matrix = digraph_gen_incidence_matrix(digraph);
    // if (test_incidence_matrix_col_sum(incidence_matrix, num_vertices, num_edges) == -1) {
    //     return 1;
    // }
    // if (test_incidence_matrix_total_rows_sum(incidence_matrix, num_vertices, num_edges) == -1) {
    //     return 1;
    // }

    // mat_print(incidence_matrix, num_vertices, num_edges);
    // digraph_free(digraph);
    // mat_free((void **)incidence_matrix, num_vertices);
    float **A = malloc(4 * sizeof(float*));
    float values[4][4] = {
        {2.0, 1.0, 3.0, 4.0},
        {8.0, 7.0, 4.0, 3.0},
        {4.0, 5.0, 1.0, 2.0},
        {1.0, 3.0, 4.0, 5.0}
    };
    for (int i = 0; i < 4; i++) {
        A[i] = malloc(4 * sizeof(float));
        for (int j = 0; j < 4; j++) {
            A[i][j] = values[i][j];
        }
    }
    float **C = malloc(4 * sizeof(float*));
    for (int i = 0; i < 4; i++) {
        C[i] = malloc(4 * sizeof(float));
        for (int j = 0; j < 4; j++) {
            C[i][j] = 0.0;
        }
    }
    mat_luf(A, 4, C);
    // for (int i = 0; i < 4; i++){
    //     for (int j = 0; j < 4; j++) {
    //         printf("%f, ", C[i][j]);
    //     }
    //     printf("\n");
    // }

    float **L = malloc(4 * sizeof(float*));
    float **U = malloc(4 * sizeof(float*));
    for (int i = 0; i < 4; i++) {
        L[i] = malloc(4 * sizeof(float));
        U[i] = malloc(4 * sizeof(float));
        for (int j = 0; j < 4; j++) {
            L[i][j] = 0;
            if (i >= j) {
                L[i][j] = C[i][j];
                if (i == j) {
                    U[i][j] = 1.0;
                }
            } else {
                U[i][j] = C[i][j];
            }
        }
    }
    printf("### L ###\n");
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++) {
            printf("%.10f, ", L[i][j]);
        }
        printf("\n");
    }
    printf("### U ###\n");
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++) {
            printf("%.10f, ", U[i][j]);
        }
        printf("\n");
    }
    float **A_prime = mat_matmul(L, U, 4, 4, 4);
    printf("### A ###\n");
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++) {
            printf("%.10f, ", A[i][j]);
        }
        printf("\n");
    }
    printf("### A' ###\n");
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++) {
            printf("%.10f, ", A_prime[i][j]);
        }
        printf("\n");
    }


}
