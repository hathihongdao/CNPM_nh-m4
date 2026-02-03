# Makefile for Coffee Shop Management System
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I./include
TARGET = coffee_shop
SRC_DIR = src
BUILD_DIR = build

# Find all source files
SRCS = $(shell find $(SRC_DIR) -name "*.cpp")
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Default target
all: $(TARGET)

# Link executable
$(TARGET): $(OBJS)
	@echo "🔗 Linking $(TARGET)..."
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "📝 Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	@echo "🚀 Running program..."
	./$(TARGET)

# Clean build files
clean:
	@echo "🧹 Cleaning..."
	rm -rf $(BUILD_DIR) $(TARGET)
	@echo "✅ Clean complete"

.PHONY: all clean run
