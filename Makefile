# Переменные
CXX = g++
CXXFLAGS = -I./include -std=c++17
LDFLAGS = -lncursesw
SRC = src/main.cpp src/game.cpp src/model.cpp src/rot_mat.cpp src/quat.cpp
OBJ = $(SRC:.cpp=.o)
OBJ := $(patsubst src/%.o,build/%.o,$(OBJ))
BUILD_DIR = build
TARGET = main

# Цель по умолчанию
all: $(TARGET)

# Создание директории build, если её нет
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Генерация объектных файлов в build/
build/%.o: src/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Сборка финальной программы
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) -o $(TARGET)

# Очистка
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Пересборка
rebuild: clean all

# Печать (опционально)
.PHONY: all clean rebuild
