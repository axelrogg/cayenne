#include <stdio.h>

extern int test_matrix();

int main() {
    printf("test_main.c :: main :: Running tests...\n");
    if (test_matrix() != 0) {
        printf("test_main.c :: main :: Some tests failed in test_matrix.c👎\n");
        return 1;
    }

    printf("test_main.c :: main :: All tests passed 👍\n");
    return 0;
}
