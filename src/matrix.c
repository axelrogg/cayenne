#include "matrix.h"

int to_buff(char *buff, size_t buff_size, int offset, const char *format, ...) {
    if (offset > 0 && (size_t)offset >= buff_size) {
        return -1;
    }

    va_list args;
    va_start(args, format);
    int num_chars = vsnprintf(buff + offset, buff_size - offset, format, args);
    va_end(args);

    if (num_chars < 0) {
        printf("to_buff :: An output error was encountered.\n");
        return -1;
    // `num_chars` is already greater than or equal to zero, so casting
    // it to a `size_t` is not a problem.
    } else if ((size_t)num_chars >= buff_size - offset) { 
        printf("to_buff :: Output was truncated.\n");
        return -1;
    }
    return num_chars;
}

int append_line_break(char *buff, size_t buff_size, int offset, int num_blocks) {
    int num_chars;
    int new_offset = 0;
    num_chars = to_buff(buff, buff_size, offset, "----");
    if (num_chars == -1) {
        return -1;
    }
    new_offset += num_chars;
    
    for (int i = 0; i < num_blocks; i++) {
        num_chars = to_buff(buff, buff_size, new_offset + offset, "+----");
        if (num_chars == -1) {
            return -1;
        }
        new_offset += num_chars;
    }

    // Add the newline character
    buff[new_offset++ + offset] = '\n';
    return new_offset;
}

void matrix_print(int **matrix, int num_rows, int num_cols) {
    char buff[MAX_BUFFER_SIZE];
    int offset = 0;
    int num_chars;

    num_chars = to_buff(buff, MAX_BUFFER_SIZE, offset, "    ");
    if (num_chars == -1) {
        return;
    }
    offset += num_chars;
    
    for (int i = 0; i < num_cols; i++) {
        if (i < 10) {
            num_chars = to_buff(buff, MAX_BUFFER_SIZE, offset, "|  %d ", i);
        }
        else {
            num_chars = to_buff(buff, MAX_BUFFER_SIZE, offset, "| %d ", i);
        }
        if (num_chars == -1) {
            return;
        }
        offset += num_chars;
    }

    // Add the newline character
    buff[offset++] = '\n';
    offset += append_line_break(buff, 1000, offset, num_cols);

    for (int i = 0; i < num_rows; i++) {
        num_chars = to_buff(buff, MAX_BUFFER_SIZE, offset, "  %d ", i);
        if (num_chars == -1) {
            return;
        }
        offset += num_chars;

        for (int j = 0; j < num_cols; j++) {
            if (matrix[i][j] >= 0) {
                num_chars = to_buff(buff, MAX_BUFFER_SIZE, offset, "|  %d ", matrix[i][j]);
            }
            else {
                num_chars = to_buff(buff, MAX_BUFFER_SIZE, offset, "| %d ", matrix[i][j]);
            }
            if (num_chars == -1) {
                return;
            }
            offset += num_chars;
        }
        buff[offset++] = '\n';
        if (i < num_rows - 1) {
            offset += append_line_break(buff, 1000, offset, num_cols);
        }
    }

    // Add the newline character
    buff[offset++] = '\n';
    buff[offset] = '\0';

    printf("%s", buff);
}
