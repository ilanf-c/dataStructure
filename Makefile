
CC ?= clang
CFLAGS ?= -O2 -Wall -Wextra -g
BUILD_DIR := build

SRCS := $(wildcard *.c)
OBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))
TARGET := $(BUILD_DIR)/main
TEST_BIN := $(BUILD_DIR)/test

# Default: build only the main program
all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link main: exclude test.c so main doesn't include the test runner
MAIN_SRCS := $(filter-out test.c,$(SRCS))
MAIN_OBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(MAIN_SRCS))

$(TARGET): $(MAIN_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Test binary objects (explicit to avoid linking main.c)
TEST_OBJS := $(BUILD_DIR)/test.o $(BUILD_DIR)/util.o $(BUILD_DIR)/InOrder_test.o $(BUILD_DIR)/InOrderThreadBinTree.o

$(TEST_BIN): $(TEST_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Build-and-run tests
.PHONY: test test-bin
test: $(BUILD_DIR) $(TEST_BIN)
	@echo "Running tests..."
	@$(TEST_BIN) all

test-bin: $(BUILD_DIR) $(TEST_BIN)
	@echo "Built test binary: $(TEST_BIN)"

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)



