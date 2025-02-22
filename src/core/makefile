# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -std=c++17 -Wall -Wextra

# Directories
SRC_DIR := sources
INC_DIR := headers
OBJ_DIR := obj
DATA_DIR := ../data

# Source files
SRCS := $(wildcard $(SRC_DIR)/*pp)

# Object files
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Executable name
TARGET := game

# Default target
all: $(TARGET)

# Rule to create object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

# Rule to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Clean rule
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Run rule
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run