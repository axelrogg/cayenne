#include <stdio.h>
#include <stdlib.h>

int vector_dfill(double *vector, int size, double values[size]) {
    if (vector == NULL || values == NULL || size <= 0)
        return -1;
    for (int i = 0; i < size; i++)
        vector[i] = values[i];
    return 0;
}

double *vector_init_zeroes_d(int size) {
    double *vector;
    if (size <= 0) {
        printf("vector.c :: vector_init_zeroes_d :: size of vector must be "
               "greater than 0.\n");
        return NULL;
    }

    vector = malloc(size * sizeof(double));
    if (vector == NULL) {
        printf("vector.c :: vector_init_zeroes_d :: vector is NULL\n");
        return NULL;
    }

    for (int i = 0; i < size; i++)
        vector[i] = 0.0;
    return vector;
}
