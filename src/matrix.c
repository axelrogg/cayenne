#include <string.h>
#include <stdio.h>

int handle_snprintf(int snprintf_returned, size_t buff_size, size_t offset) {
    if (snprintf_returned < 0) {
        printf("encoding error\n");
        return -1;
    // `snprintf_returned` is already greater than or equal to zero, so casting
    // it to a `size_t` is not a problem.
    } else if ((size_t)snprintf_returned >= buff_size - offset) { 
        printf("output was truncated\n");
        return -1;
    }
    return 0;
}

int add_line_break(char *buff, size_t buff_size, int offset, int num_blocks) {
    // We add 1 to `num_blocks` because we want more space for the far-left column
    // (where the row indexes go).
    for (int i = 0; i < num_blocks + 1; i++) {
        int num_chars;
        if (i == 0) {
            num_chars = snprintf(buff + offset, buff_size - offset, "----");
        } else {
            num_chars = snprintf(buff + offset, buff_size - offset, "+----");
        }
        if (handle_snprintf(num_chars, buff_size, offset) == -1) {
            return -1;
        }
        offset += num_chars;
    }

    // Add the newline character
    int num_chars = snprintf(buff + offset, buff_size - offset, "\n");
    offset += num_chars;
    if (handle_snprintf(num_chars, buff_size, offset) == -1) {
        return -1;
    }
    return offset;
}


int add_first_row(char *buff, size_t buff_size, int offset, int num_blocks) {
    int num_chars;
    num_chars = snprintf(buff + offset, buff_size - offset, "    ");
    if (handle_snprintf(num_chars, buff_size, offset) == -1) {
        return -1;
    } 
    offset += num_chars;
    
    // We add 1 to `num_blocks` because we want more space for the far-left column
    // (where the row indexes go).
    for (int i = 0; i < num_blocks; i++) {
        if (i < 10) {
            num_chars = snprintf(buff + offset, buff_size - offset, "|  %d ", i);
        }
        else {
            num_chars = snprintf(buff + offset, buff_size - offset, "| %d ", i);
        }
        if (handle_snprintf(num_chars, buff_size, offset) == -1) {
            return -1;
        }    
        offset += num_chars;
    }

    // Add the newline character
    num_chars = snprintf(buff + offset, buff_size - offset, "\n");
    offset += num_chars;
    if (handle_snprintf(num_chars, buff_size, offset) == -1) {
        return -1;
    }
    return offset;
}

int add_values_row(char *buff, size_t buff_size, int offset, int **matrix, int num_rows, int num_cols) {
    int num_chars;
    for (int i = 0; i < num_rows; i++) {
    num_chars = snprintf(buff + offset, buff_size - offset, "  %d ", i);
    if (handle_snprintf(num_chars, buff_size, offset) == -1) {
        printf("something weird happened\n");
        return -1;
    }
    offset += num_chars;

        for (int j = 0; j < num_cols; j++) {
            num_chars = 0;
            if (matrix[i][j] >= 0) {
                num_chars = snprintf(buff + offset, buff_size - offset, "|  %d ", matrix[i][j]);
            }
            else {
                num_chars = snprintf(buff + offset, buff_size - offset, "| %d ", matrix[i][j]);
            }
            if (handle_snprintf(num_chars, buff_size, offset) == -1) {
                printf("something weird happened\n");
                return -1;
            }
            offset += num_chars;
        }
        num_chars = snprintf(buff + offset, buff_size - offset, "\n");
        offset += num_chars;
        if (handle_snprintf(num_chars, buff_size, offset) == -1) {
            printf("something weird happened\n");
            return -1;
        }
        if (i < num_rows - 1) {
            offset = add_line_break(buff, 1000, offset, num_cols);
        }
    }

    // Add the newline character
    num_chars = 0;
    num_chars = snprintf(buff + offset, buff_size - offset, "\n");
    offset += num_chars;
    if (handle_snprintf(num_chars, buff_size, offset) == -1) {
        printf("something weird happened\n");
        return -1;
    }
    buff[offset] = '\0';
    return offset;
}

void matrix_print(int **matrix, int num_rows, int num_cols) {
    const int BUFF_SIZE = 500;
    char buff[BUFF_SIZE];
    int offset = 0;
    offset = add_first_row(buff, BUFF_SIZE, offset, num_cols);
    offset = add_line_break(buff, BUFF_SIZE, offset, num_cols);
    offset = add_values_row(buff, BUFF_SIZE, offset, matrix, num_rows, num_cols);
    printf("Matrix values\n-------------\n%s", buff);
}
