#include <stdio.h>

extern int test_matrix();

int main() {
    printf("Running tests...\n");
    if (test_matrix() != 0) {
        printf("Some tests failed in test_matrix.c \n");
        return 1;
    }

    printf("All tests passed\n");
    return 0;
}
