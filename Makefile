# Compiler
CC = gcc
# Compiler flags
CFLAGS = -Isrc -g -Wall -Wextra -std=c99

# Directories
SRC_DIR = src
OBJ_DIR = obj

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
# Object files
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Main target
TARGET = cayenne

# debug: $(TARGET)
# 	gdb $(TARGET)

# Default target
all: $(TARGET)

# Linking the main executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Compiling each source file into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create the obj directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Phony targets
.PHONY: all clean
