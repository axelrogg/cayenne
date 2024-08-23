#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"

double drand(double min, double max) {
    srand(time(NULL));
    if (min < 0) {
        printf("matrix.c :: drand :: min cannot be less than 0\n");
        return -1;
    }
    if (max > RAND_MAX) {
        printf("matrix.c :: drand :: max cannot be greater than %i\n", RAND_MAX);
        return -1;
    }
    return ((double)rand() * (max - min) / (double)RAND_MAX) + min;
}

double rel_error(double m_val, double t_val) {
    return fabs(m_val - t_val) / t_val;
}

