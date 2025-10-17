CC := clang
CFLAGS := -Wall -Wextra -std=c11
SRC_DIR := src
BUILD_DIR := build
TARGET := chip8
SRCS := $(SRC_DIR)/main.c \
        $(SRC_DIR)/cpu.c \
        $(SRC_DIR)/display.c \
        $(SRC_DIR)/input.c
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
all: $(TARGET)
$(TARGET): $(OBJS)
	@echo "🔗 Linking..."
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@echo "⚙️  Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	@echo "🧹 Cleaning..."
	rm -rf $(BUILD_DIR) $(TARGET)
rebuild: clean all
run: $(TARGET)
	./$(TARGET) $(ROM)
.PHONY: all clean rebuild run
