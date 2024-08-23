#include <stdio.h>
#include <time.h>

extern int test_matrix();
extern int test_linalg();

int main(void) {
    clock_t t_start, t_end;
    double cpu_time_taken;
    t_start = clock();

    printf("test_main.c :: main :: Running tests...\n");

    if (test_matrix() != 0) {
        printf("test_main.c :: main :: Some tests failed in test_matrix.c 👎\n");
        return -1;
    }

    if (test_linalg() != 0) {
        printf("test_main.c :: main :: Some tests failed in test_linalg.c 👎\n");
        return -1;
    }

    t_end = clock();
    cpu_time_taken = ((double) (t_end - t_start)) / CLOCKS_PER_SEC;
    printf("test_main.c :: main :: All tests passed 👍\n");
    printf("test_main.c :: main :: Time taken: %e seconds\n", cpu_time_taken);

    return 0;
}
