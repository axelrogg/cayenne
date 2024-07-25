#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"


/**
 * @brief Returns a pseudo-random float within the range [`min`, `max`].
 *
 * This function uses `rand` from the Standard C library to generate a pseudo-
 * random floating point number that lies in the range [`min`, `max`].
 *
 * @param min: The minimum value `randf` can return.
 * @param max: The maximum value `randf` can return.
 *
 * @return Returns a float or `-1` if `min` is less than 0 or if `max` is
 *         greater than `RAND_MAX`
 */
float randf(float min, float max) {
    srand(time(NULL));
    if (min < 0) {
        printf("matrix.c :: randf :: min cannot be less than 0\n");
        return -1;
    }
    if (max > RAND_MAX) {
        printf("matrix.c :: randf :: max cannot be greater than %i\n", RAND_MAX);
        return -1;
    }
    return ((float)rand() * (max - min) / (float)RAND_MAX) + min;
}

