# the compiler: clang++ for C++ program
CC = clang++

# compiler flags:
#  -std=c++17 - this flag specifies the C++ standard to use
#  -stdlib=libc++ - this flag specifies the standard library to use
#  -g - adds debugging information to the executable file
#  -Wall - turns on most compiler warnings
CFLAGS = -std=c++17 -stdlib=libc++ -g -Wall

# Directories
SRC_DIR = src/core
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

# The build target
TARGET = $(BUILD_DIR)/game

# List of source files
SRCS = card.cpp deck.cpp file_utils.cpp game.cpp player.cpp supply.cpp

# List of object files
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Default target
all: $(TARGET)

# Rule to compile each source file into an object file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean up the build
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
