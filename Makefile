CXX := g++
CXXFLAGS := -Wall -std=c++11 -O3
LDLIBS := -lglfw -lm -lGL -lGLU -lglut -lpthread

BIN_DIR := bin
OBJ_DIR := obj
SRC_DIR := src
INCLUDE := -Iinclude
TARGET ?= Release
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

all: $(BIN_DIR)/$(TARGET)/DodgeTheBalls

$(BIN_DIR)/$(TARGET)/DodgeTheBalls: $(OBJECTS)
	mkdir -p $(BIN_DIR)/$(TARGET)
	$(CXX) $(CPPFLAGS) $^ -o $@ $(LDLIBS)

$(OBJECTS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@ $(LDLIBS)

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

.PHONY: all clean
