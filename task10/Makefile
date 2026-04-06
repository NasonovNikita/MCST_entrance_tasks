CXX = g++
LDFLAGS = -lm
CXXFLAGS ?= -Wall -Wextra -Werror
DEPFLAGS = -MMD

SRC_DIR = ./src
INC_DIR = ./include
BUILD_DIR = ./build
OBJ_DIR = ${BUILD_DIR}/obj
BIN_DIR = ${BUILD_DIR}/bin

TARGET = $(BIN_DIR)/task10

SRCS = $(shell find $(SRC_DIR) -name "*.cpp")
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

CXXFLAGS += -I$(INC_DIR)

# For CLion to configure project correctly
all: $(TARGET)

$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)


debug: CXXFLAGS += -DDEBUG -g
debug: clean $(TARGET)

-include $(DEPS)

clean:
	rm -rf $(BUILD_DIR)

run: $(TARGET)
	$(TARGET)

.PHONY: all debug clean run
