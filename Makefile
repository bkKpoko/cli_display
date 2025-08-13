# Compiler flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2

# Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Binary file
TARGET = main

# Sources
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Headers
INCLUDES = -I$(INC_DIR)
LIBS = -lncursesw -lpanelw


# Main rule
all: $(BUILD_DIR) $(TARGET)

# Build dir
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build target
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LIBS) -o $@ $^

# .cpp to .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LIBS) -c $< -o $@

# clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

rebuild: clean all

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean rebuild run
