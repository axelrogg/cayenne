#include "digraph.h"
#include "matrix.h"

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
    int num_vertices = 3;
    int num_edges = 3;
    int edges[3][2] = {
        {0, 1},
        {0, 2},
        {1, 2},
    };
    
    Digraph *digraph = digraph_build(num_vertices, num_edges, edges);
    digraph_print(digraph);
    printf("Number of edges: %d\n", digraph_num_edges(digraph));
    int **incidence_matrix = digraph_gen_incidence_matrix(digraph);
    if (test_incidence_matrix_col_sum(incidence_matrix, num_vertices, num_edges) == -1) {
        return 1;
    }
    if (test_incidence_matrix_total_rows_sum(incidence_matrix, num_vertices, num_edges) == -1) {
        return 1;
    }

    matrix_print(incidence_matrix, num_vertices, num_edges);
    digraph_free(digraph);
    digraph_free_incidence_matrix(incidence_matrix, num_vertices);
}
