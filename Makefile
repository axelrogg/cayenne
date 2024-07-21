# Compiler
CC = gcc
# Compiler flags
CFLAGS = -Isrc -g -Wall -Wextra -std=c99

# Directories
SRC_DIR = src
OBJ_DIR = obj
TEST_DIR = tests
TEST_OBJ_DIR = $(OBJ_DIR)/tests

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(filter-out $(SRC_DIR)/cayenne.c,$(SRCS)))
MAIN_OBJ = $(OBJ_DIR)/cayenne.o

# Test source files
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)

# Test object files
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c,$(TEST_OBJ_DIR)/%.o,$(TEST_SRCS))


################# Targets #################

# Main target
TARGET = cayenne
TEST_TARGET = test_cayenne

# debug: $(TARGET)
# 	gdb $(TARGET)

# Default target
all: $(TARGET)

################# End of targets #################


################# Linking #################

# Linking the main executable
$(TARGET): $(MAIN_OBJ) $(OBJS)
	$(CC) $(CFLAGS) $(MAIN_OBJ) $(OBJS) -o $@

# Linking the test executable
$(TEST_TARGET): $(OBJS) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(TEST_OBJS) -o $@

################# End of linking #################


################# Compiling #################

# Compiling each source file into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compiling each test file into object files
$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.c | $(TEST_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

################# End of compiling #################

# Create the obj directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Create the test obj directory if it doesn't exist
$(TEST_OBJ_DIR):
	mkdir -p $(TEST_OBJ_DIR)

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(TEST_TARGET)

# Phony targets
.PHONY: all clean test

# Test target
test: $(TEST_TARGET)
	./$(TEST_TARGET)
